import React from "react";
import { useParams } from "react-router-dom";

const ProductDetail = ({ products }) => {
    const { id } = useParams();
    const product = products.find((p) => p._id === id);

    if (!product) {
        return <div>Product not found</div>;
    }

    return (
        <div>
            <h1>{product.name}</h1>
            <p>Product ID: {product._id}</p>
            <p>Price: {product.price}</p>
        </div>
    );
};

export default ProductDetail;
