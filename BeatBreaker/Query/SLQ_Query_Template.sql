
--DROP TABLE users;

CREATE TABLE users (
    id INT PRIMARY KEY IDENTITY(1,1),
    username VARCHAR(50) NOT NULL,
    score int NOT NULL,
    created_at DATETIME DEFAULT GETDATE()
);

INSERT INTO users (username, score) VALUES ('Blake Fitzpatrick', 100);
INSERT INTO users (username, score) VALUES ('Big Man Sam', 999);
INSERT INTO users (username, score) VALUES ('ABCDEFG', 123);
INSERT INTO users (username, score) VALUES ('CoolName', 450);
INSERT INTO users (username, score) VALUES ('Seanie', 200);
INSERT INTO users (username, score) VALUES ('MDOG', 320);
INSERT INTO users (username, score) VALUES ('Rob', 200);
INSERT INTO users (username, score) VALUES ('S', 500);
INSERT INTO users (username, score) VALUES ('Keane', 700);
INSERT INTO users (username, score) VALUES ('ASD', 600);
INSERT INTO users (username, score) VALUES ('Liam', 777);

SELECT * FROM users;

