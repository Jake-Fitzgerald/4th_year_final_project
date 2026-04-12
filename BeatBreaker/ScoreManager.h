#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

struct SongScore
{
	std::string songName;
	int score;
};

class ScoreManager
{
public:
	ScoreManager();

	void loadScores();
	void saveScores();

	int getPB(std::string& t_songName);

	bool updatePB(std::string t_songName, int t_score);

private:
	std::string m_filePath = "ASSETS\\SAVEDATA\\Highscores_Saves\\scores.txt";
	std::vector<SongScore> m_scoreVec;
};

