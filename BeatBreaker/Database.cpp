#include "Database.h"


bool Database::sqlConnect(std::string t_ODBCString)
{


	// Setup environment
	SQLRETURN returnAllocCheck;

	returnAllocCheck = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &handleEnvir);
	if (returnAllocCheck != SQL_SUCCESS && returnAllocCheck != SQL_SUCCESS_WITH_INFO)
	{
		std::cerr << "Allocation connection failed" << std::endl;
		return 1;
	}

	SQLSetEnvAttr(handleEnvir, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);

	SQLAllocHandle(SQL_HANDLE_DBC, handleEnvir, &handleDbc);

	// Connect with the token
	//std::wstring ODBCTokenW(ODBCToken.begin(), ODBCToken.end());

	SQLRETURN returnDriverCheck = SQLDriverConnectA(handleDbc, NULL, (SQLCHAR*)t_ODBCString.c_str(), SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);
	if (returnDriverCheck != SQL_SUCCESS && returnDriverCheck != SQL_SUCCESS_WITH_INFO)
	{
		std::cerr << "Driver connection failed" << std::endl;
		return false;
	}
	else
	{
		std::cerr << "Driver connection SUCCESS!" << std::endl;
		return true;
	}

	// ---------------------------------------------------------------------------------------------------------------------------------------------------
	

}

std::vector<USERDATA> Database::getLeaderboardData()
{
	std::vector<USERDATA> leaderboardVec;

	// Query
	SQLAllocHandle(SQL_HANDLE_STMT, handleDbc, &handleStatement);

	SQLRETURN returnExecCheck; // 
	//returnExecCheck = SQLExecDirectA(handleStatement, (SQLCHAR*)"SELECT id, username, score FROM users", SQL_NTS);
	returnExecCheck = SQLExecDirectA(handleStatement, (SQLCHAR*)"SELECT id, username, score FROM users", SQL_NTS);
	if (returnExecCheck != SQL_SUCCESS && returnExecCheck != SQL_SUCCESS_WITH_INFO)
	{
		SQLCHAR sqlState[6];
		SQLINTEGER nativeError;
		SQLCHAR messageText[SQL_MAX_MESSAGE_LENGTH];
		SQLSMALLINT textLength;

		SQLRETURN diagRet = SQLGetDiagRecA(
			SQL_HANDLE_STMT,
			handleStatement,
			1,
			sqlState,
			&nativeError,
			messageText,
			SQL_MAX_MESSAGE_LENGTH,
			&textLength
		);

		if (diagRet == SQL_SUCCESS || diagRet == SQL_SUCCESS_WITH_INFO)
		{
			std::cerr << "SQLState: " << sqlState << std::endl;
			std::cerr << "NativeError: " << nativeError << std::endl;
			std::cerr << "Message: " << messageText << std::endl;
		}

		std::cerr << "ExecDirect connection failed (query)" << std::endl;
		//return 1;
	}
	else
	{
		std::cerr << "ExecDirect connection SUCCESS!" << std::endl;
	}



	// ---------------------------------------------------------------------------------------------------------------------------------------------------
	// Variables
	int  id;
	char username[50];
	int  score;

	// Grab the variables
	SQLBindCol(handleStatement, 1, SQL_C_LONG, &id, sizeof(id), NULL);
	SQLBindCol(handleStatement, 2, SQL_C_CHAR, username, sizeof(username), NULL);
	SQLBindCol(handleStatement, 3, SQL_C_LONG, &score, sizeof(score), NULL);

	// Fetch
	SQLRETURN returnFetch;

	while ((returnFetch = SQLFetch(handleStatement)) == SQL_SUCCESS)
	{
		std::cerr << "ID: " << id << ", ";
		std::cerr << "Username: " << username << ", ";
		std::cerr << "Score: " << score << std::endl;


		USERDATA entry;
		entry.id = id;
		entry.username = std::string(username);
		entry.score = score;
		leaderboardVec.push_back(entry);
	}

	if (returnFetch != SQL_NO_DATA)
	{
		std::cerr << "Fetch failed" << std::endl;;
	}

	SQLCleanup(handleEnvir, handleDbc, handleStatement);

	return leaderboardVec;
}

bool Database::submitScore(std::string t_username, int t_score)
{
	SQLAllocHandle(SQL_HANDLE_STMT, handleDbc, &handleStatement);

	std::string query = "INSERT INTO users (username, score) VALUES ('" + t_username + "', " + std::to_string(t_score) + ")";

	SQLRETURN returnExecCheck = SQLExecDirectA(handleStatement, (SQLCHAR*)query.c_str(), SQL_NTS);

	if (returnExecCheck != SQL_SUCCESS && returnExecCheck != SQL_SUCCESS_WITH_INFO)
	{
		std::cerr << "Submit score failed" << std::endl;
		SQLCleanup(handleEnvir, handleDbc, handleStatement);
		return false;
	}

	std::cerr << "Submit score SUCCESS!" << std::endl;
	SQLCleanup(handleEnvir, handleDbc, handleStatement);
	return true;
}

void Database::SQLCleanup(SQLHENV& t_handleEnvir, SQLHDBC& t_handleDbc, SQLHSTMT& t_handleStatement)
{
	SQLFreeHandle(SQL_HANDLE_STMT, t_handleStatement);
	SQLDisconnect(t_handleDbc);
	SQLFreeHandle(SQL_HANDLE_DBC, t_handleDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, t_handleEnvir);
}
