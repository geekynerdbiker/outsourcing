import React, { useEffect, useState } from "react";
import { Link } from "react-router-dom";
import axios from "axios";

function HomePage({ setProducts }) {   
    const [products, setLocalProducts] = useState([]);
    useEffect(() => {
        const fetchProducts = async () => {
            try {
                const response = await axios.get("http://localhost:5000/api/products");
                console.log("Fetched products:", response.data);
                setLocalProducts(response.data);
                setProducts(response.data);
            } catch (error) {
                console.error("Error fetching products:", error);
            }
        };

        fetchProducts();
    }, [setProducts]);

    return (
        <div>
            <h1>Home Page</h1>
            
            <div>
                {products.map((product) => (
                    <Link to={`/product/${product._id}`} key={product._id}>
                        <div>{product.name}</div>
                    </Link>
                ))}
            </div>
        </div>
    );
}

export default HomePage;