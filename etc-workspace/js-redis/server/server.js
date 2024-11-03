const express = require("express");
const session = require("express-session");

const redis = require("redis");
const connectRedis = require("connect-redis");

const mongoose = require("mongoose");
const cors = require("cors");

const dotenv = require("dotenv");

const app = express();
const PORT = process.env.PORT || 5000;

app.use(cors({
    origin: "http://localhost:3000"
}));
dotenv.config();

mongoose.connect(process.env.MONGODB_URI, {
    useNewUrlParser: true,
    useUnifiedTopology: true,
})
.then(() => console.log("MongoDB connected"))
.catch(err => console.log("MongoDB connection error: ", err));

const productSchema = new mongoose.Schema({
    _id: String,
    name: String,
    price: String
});

const Product = mongoose.model("Product", productSchema, "products");

app.get("/api/products", async (req, res) => {
    try {
        const products = await Product.find();
        res.json(products);
    } catch (error) {
        res.status(500).json({ message: "Internal server error" });
    }
});

const redisClient = Redis.createClient();
redisClient.connect().catch(console.error);

const RedisStore = connectRedis(session);

app.use(
    session({
        store: new RedisStore({ client: redisClient }),
        secret: "secret",
        resave: false,
        saveUninitialized: false,
        cookie: { secure: false },
    })
);

app.get("/api/search/:query", async (req, res) => {
    const query = req.params.query;

    const cachedResult = await redisClient.get(query);
    if (cachedResult) {
        return res.json(JSON.parse(cachedResult));
    }

    try {
        const products = await Product.find({ name: { $regex: query, $options: "i" } }); // 대소문자 구분 없이 검색
        redisClient.set(query, JSON.stringify(products), "EX", 3600); // 캐시에 1시간 저장
        return res.json(products);
    } catch (error) {
        return res.status(500).json({ error: "Error fetching products" });
    }
});

app.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
});
