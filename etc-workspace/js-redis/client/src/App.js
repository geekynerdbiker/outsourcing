import React, { useState } from "react";
import { BrowserRouter as Router, Route, Routes } from "react-router-dom";

import HomePage from "./HomePage";
import TestPage from "./TestPage";
import ProductDetail from "./ProductDetail";

const App = () => {
  const [products, setProducts] = useState([]);

    return (
          <Router>
            <Routes>
              <Route path="/" element={<HomePage setProducts={setProducts}/>} />
              <Route path="/product/:id" element={<ProductDetail products={products} />} />
              <Route path="/test" element={<TestPage />} />
            </Routes>
          </Router>
    );
};

export default App;
