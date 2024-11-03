import React, { useState } from "react";
import axios from "axios";

const TestPage = () => {
    const [inputValue, setInputValue] = useState("");
    const [response, setResponse] = useState(null);

    const handleApiCall = async () => {
        try {
            const result = await axios.get(`http://localhost:5000/api/search/${inputValue}`);
            setResponse(result.data);
        } catch (error) {
            console.error("Error fetching data:", error);
            setResponse(null);
        }
    };

    return (
        <div>
            <h1>Test Page</h1>
            <input
                type="text"
                value={inputValue}
                onChange={(e) => setInputValue(e.target.value)}
                placeholder="Enter search query"
            />
            <button onClick={handleApiCall}>Search</button>
            {response && (
                <div>
                    <h2>Response:</h2>
                    <pre>{JSON.stringify(response, null, 2)}</pre>
                </div>
            )}
        </div>
    );
};

export default TestPage;
