
CREATE TABLE users (
    id INT PRIMARY KEY IDENTITY(1,1),
    username VARCHAR(50) NOT NULL,
    score int(50) NOT NULL,
    created_at DATETIME DEFAULT GETDATE()
);

INSERT INTO users (username)
VALUES ('Blake Fitzpatrick');

SELECT * FROM users;

