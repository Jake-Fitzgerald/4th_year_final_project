#include "ScoreManager.h"

ScoreManager::ScoreManager()
{
}

void ScoreManager::loadScores()
{
	std::ifstream file(m_filePath);
	if (!file.is_open())
	{
		std::cerr << "[Score Manager] No scores file found" << std::endl;
		return;
	}

	m_scoreVec.clear();

	std::string currentLine;
	while (std::getline(file, currentLine))
	{
		int pos = -1;

		for (int i = 0; i < currentLine.length(); i++)
		{
			if (currentLine[i] == '=')
			{
				pos = i;
				break;
			}
		}

		// Skip shoddy lines
		if (pos == -1)
		{
			continue;
		}

		// Split name and score
		std::string name = currentLine.substr(0, pos);
		std::string amount = currentLine.substr(pos + 1);

		int value = std::stoi(amount);

		SongScore entry;
		entry.songName = name;
		entry.score = value;
		m_scoreVec.push_back(entry);

		std::cerr << "[Score Manager] Loaded scores" << name << " = " << value << std::endl;
	}

	file.close();
}

void ScoreManager::saveScores()
{
	std::ofstream file(m_filePath);

	if (!file)
	{
		std::cerr << "[Score Manager] Couldn't open score text file for saving" << std::endl;
	}

	for (int i = 0; i < m_scoreVec.size(); i++)
	{
		file << m_scoreVec[i].songName << "=" << m_scoreVec[i].score << "\n";
	}

	file.close();
}

int ScoreManager::getPB(std::string& t_songName)
{
	for (int i = 0; i < m_scoreVec.size(); i++)
	{
		if (m_scoreVec[i].songName == t_songName)
		{
			return m_scoreVec[i].score;
		}
	}

	return 0;
}

bool ScoreManager::updatePB(std::string t_songName, int t_score)
{
	// Check if this song already has saved data
	for (int i = 0; i < m_scoreVec.size(); i++)
	{
		if (m_scoreVec[i].songName == t_songName)
		{
			if (t_score > m_scoreVec[i].score)
			{
				m_scoreVec[i].score = t_score;
				saveScores();

				std::cerr << "[Score Manager] New personal best for: " << t_songName  << ": " << t_score << std::endl;
				return true;
			}
			std::cerr << "[Score Manager] Didn't beat personal best" << std::endl;
			return false;
		}
	}

	// No saved data for this song os make one
	SongScore newEntry;
	newEntry.songName = t_songName;
	newEntry.score = t_score;

	m_scoreVec.push_back(newEntry);

	saveScores();

	std::cerr << "[Score Manager] Score for: " << t_songName << " - " << t_score << std::endl;


	return false;
}
