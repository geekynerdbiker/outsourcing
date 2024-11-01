CREATE TABLE EmotionLog (
    id INT AUTO_INCREMENT PRIMARY KEY,
    timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    overall_emotion VARCHAR(50) NOT NULL,
    sorrow_likelihood INT,
    anger_likelihood INT,
    joy_likelihood INT,
    surprise_likelihood INT
);
