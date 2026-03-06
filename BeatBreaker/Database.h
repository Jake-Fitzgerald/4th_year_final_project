#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <windows.h>


#include <sql.h>
#include <sqlext.h>
#pragma comment(lib, "odbc32.lib")

struct USERDATA
{
	int id = -1;
	std::string username = " ";
	int score = -1;
};

class Database
{
public:
	bool sqlConnect(std::string t_ODBCString);
	std::vector<USERDATA> getLeaderboardData();

	void SQLCleanup(SQLHENV& t_handleEnvir, SQLHDBC& t_handleDbc, SQLHSTMT& t_handleStatement);

private:
	SQLHENV handleEnvir;
	SQLHDBC handleDbc;
	SQLHSTMT handleStatement;
};

