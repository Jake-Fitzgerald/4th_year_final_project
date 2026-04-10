#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <windows.h>
#include "Globals.h"
#include <fstream> 

#include <sql.h>
#include <sqlext.h>
#pragma comment(lib, "odbc32.lib")

/*
Notes:
 
Another query call when pulling if we want the list to be ordered:
"SELECT id, username, score FROM users ORDER BY score DESC"

*/

//struct USERDATA
//{
//	int id = -1;
//	std::string username = " ";
//	int score = -1;
//};

class Database
{
public:
	bool sqlConnect(std::string t_ODBCString);
	std::vector<USERDATA> getLeaderboardData();

	bool submitScore(std::string t_username, int t_score);
	bool submitScoreFromFile(std::string t_filePath);

	bool submitResult(std::string t_username, std::string t_songName, SessionStats& t_stats);

	bool uploadMIDI(std::string& t_filePath, std::vector<uint8_t>& t_outputBuffer);

	void SQLCleanup(SQLHENV& t_handleEnvir, SQLHDBC& t_handleDbc, SQLHSTMT& t_handleStatement);

private:
	SQLHENV handleEnvir;
	SQLHDBC handleDbc;
	SQLHSTMT handleStatement;
};

