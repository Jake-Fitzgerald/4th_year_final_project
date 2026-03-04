#include <iostream>
#include <windows.h>         


#include <string>
#include <sql.h>
#include <sqlext.h>


#pragma comment(lib, "odbc32.lib")

/*
Notes:

Visual Studio paths:
C:\Program Files (x86)\Windows Kits\10\Include\10.0.26100.0\um
C:\Program Files (x86)\Windows Kits\10\Lib\10.0.26100.0\um\x64


SQLHENV - global ODBC environment that we create at the start once.
SQLHDBC - a single connection to the database
SQLHSTMT - a single query on that connection (SQLHDBC)

Return codes:
	SQL_SUCCESS
	SQL_SUCCESS_WITH_INFO
	SQL_ERROR
	SQL_INVALID_HANDLE
	SQL_NO_DATA_FOUND
	SQL_NEED_DATA

*/

void SQLCleanup(SQLHENV& t_handleEnvir, SQLHDBC& t_handleDbc, SQLHSTMT& t_handleStatement)
{
	SQLFreeHandle(SQL_HANDLE_STMT, t_handleStatement);
	SQLDisconnect(t_handleDbc);
	SQLFreeHandle(SQL_HANDLE_DBC, t_handleDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, t_handleEnvir);
}

int main(int argc, char* argv[])
{
	std::string ODBCToken = argv[1];


	// Print Token
	//std::cerr << ODBCToken << std::endl;


	SQLHENV handleEnvir;
	SQLHDBC handleDbc;
	SQLHSTMT handleStatement;

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

	SQLRETURN returnDriverCheck = SQLDriverConnectA(handleDbc, NULL, (SQLCHAR*)ODBCToken.c_str(), SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);
	if (returnDriverCheck != SQL_SUCCESS && returnDriverCheck != SQL_SUCCESS_WITH_INFO)
	{

		std::cerr << "Driver connection failed" << std::endl;
		return 1;
	}



	// ---------------------------------------------------------------------------------------------------------------------------------------------------
	// Query
	SQLAllocHandle(SQL_HANDLE_STMT, handleDbc, &handleStatement);

	SQLRETURN returnExecCheck;
	returnExecCheck = SQLExecDirectA(handleStatement, (SQLCHAR*)"SELECT id, username, score FROM users", SQL_NTS);
	if (returnExecCheck != SQL_SUCCESS && returnExecCheck != SQL_SUCCESS_WITH_INFO)
	{
		std::cerr << "ExecDirect connection failed (query)" << std::endl;
		return 1;
	}

	// Variables
	int  id;
	char username[50];
	int  score;

	// Grab the variables
	SQLBindCol(handleStatement, 1, SQL_C_LONG, &id, 0, NULL);
	SQLBindCol(handleStatement, 2, SQL_C_CHAR, username, sizeof(username), NULL);
	SQLBindCol(handleStatement, 3, SQL_C_LONG, &score, 0, NULL);

	// Fetch
	SQLRETURN returnFetch;

	while ((returnFetch = SQLFetch(handleStatement)) == SQL_SUCCESS) 
	{
										std::cerr << "ID: " << id << std::endl;
										std::cerr << "Username: " << username << std::endl;
										std::cerr << "Score: " << score << std::endl;
	}

	if (returnFetch != SQL_NO_DATA)
	{
		std::cerr << "Fetch failed" << std::endl;;
	}

	std::cin;

	SQLCleanup(handleEnvir, handleDbc, handleStatement);

	return 0;
}

