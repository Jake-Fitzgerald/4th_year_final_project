-----------------------------
-- Drop tables
-----------------------------
DROP TABLE IF EXISTS results;
DROP TABLE IF EXISTS songs;
DROP TABLE IF EXISTS users;


-----------------------------
-- Users
-----------------------------
CREATE TABLE users (
	id INT PRIMARY KEY IDENTITY(1,1),
	username VARCHAR(50) NOT NULL
);


-----------------------------
-- Songs
-----------------------------
CREATE TABLE songs (
	id INT PRIMARY KEY IDENTITY(1,1),
	song_name VARCHAR(50) NOT NULL
);


-----------------------------
-- Results
-----------------------------
CREATE TABLE results (
	id INT PRIMARY KEY IDENTITY(1,1),

	user_id INT,
	song_id INT,

	score INT,
	early_notes INT,
	perfect_notes INT,
	late_notes INT,
	missed_notes INT,
	wrong_notes INT
);

-----------------------------
-- Insert Users
-----------------------------
INSERT INTO users (username) VALUES ('Blake Fitzpatrick');
INSERT INTO users (username) VALUES ('Big Man Sam');
INSERT INTO users (username) VALUES ('ABCDEF');
INSERT INTO users (username) VALUES ('CoolName');
INSERT INTO users (username) VALUES ('Seanie');


-----------------------------
-- Insert Songs
-----------------------------
INSERT INTO songs (song_name) VALUES ('Song 1');
INSERT INTO songs (song_name) VALUES ('Song 2');
INSERT INTO songs (song_name) VALUES ('Song 3');


-----------------------------
-- Insert Results
-----------------------------
INSERT INTO results (user_id, song_id, score, early_notes, perfect_notes, late_notes, missed_notes, wrong_notes)
VALUES (1, 1, 100, 5, 10, 3, 2, 0);

INSERT INTO results (user_id, song_id, score, early_notes, perfect_notes, late_notes, missed_notes, wrong_notes)
VALUES (2, 1, 300, 2, 1, 6, 11, 2);

INSERT INTO results (user_id, song_id, score, early_notes, perfect_notes, late_notes, missed_notes, wrong_notes)
VALUES (3, 2, 10, 50, 30, 5, 2, 2);

INSERT INTO results (user_id, song_id, score, early_notes, perfect_notes, late_notes, missed_notes, wrong_notes)
VALUES (4, 3, 60, 2, 8, 9, 5, 9);

INSERT INTO results (user_id, song_id, score, early_notes, perfect_notes, late_notes, missed_notes, wrong_notes)
VALUES (5, 2, 800, 7, 7, 7, 7, 7);


-----------------------------
-- Load
-----------------------------
SELECT * FROM users;
SELECT * FROM songs;
SELECT * FROM results;
	