#include "Database.h"


bool Database::sqlConnect(std::string t_ODBCString)
{
	std::cerr << "" << std::endl;
	std::cerr << "" << std::endl;
	std::cerr << "=======================" << std::endl;
	std::cerr << "Connecting to server..." << std::endl;
	std::cerr << "=======================" << std::endl;

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
		std::cerr << "-> Driver connection FAILED" << std::endl;
		b_isConnected = false;
		return false;
	}
	else
	{
		std::cerr << "-> Driver connection SUCCESS!" << std::endl;
		b_isConnected = true;
		return true;
	}
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

	SQLCleanup(/*handleEnvir, handleDbc, handleStatement*/);

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
		SQLCleanup(/*handleEnvir, handleDbc, handleStatement*/);
		return false;
	}

	std::cerr << "Submit score SUCCESS!" << std::endl;
	SQLCleanup(/*handleEnvir, handleDbc, handleStatement*/);
	return true;
}

bool Database::submitScoreFromFile(std::string t_filePath)
{
	std::ifstream file(t_filePath);
	

	if (!file.is_open())
	{
		std::cerr << "Failed to open score file" << std::endl;
		return false;
	}

	std::string currentLine;
	while (std::getline(file, currentLine))
	{
		std::cerr << currentLine << std::endl;

		int pos = -1;
		// Find ',' using a normal for loop
		for (int i = 0; i < currentLine.length(); i++)
		{
			if (currentLine[i] == ',')
			{
				pos = i;
				break;
			}
		}
		// Skip any bad lines
		if (pos == -1)
		{
			continue;
		}

		// Split username and score (before , is username, after , is score)
		std::string username = currentLine.substr(0, pos);
		std::string scoreStr = currentLine.substr(pos + 1);
		// Convert the string to a number
		int score = std::stoi(scoreStr);

		std::cerr << "Username: " << username << " Score: " << score << std::endl;
		submitScore(username, score);
	}

	file.close();

	SQLCleanup(/*handleEnvir, handleDbc, handleStatement*/);
	return true;
}

bool Database::submitResult(std::string t_username, std::string t_songName, SessionStats& t_stats, std::string t_fileMidiPath)
{
	// IDs
	int songID = getSongID(t_songName);
	if (songID == -1)
	{
		std::cerr << "[DB] Song ID wasn't found and can't submit" << std::endl;
		return false;
	}

	int userID = getUserID(t_username);
	if (userID == -1)
	{
		std::cerr << "[DB] User ID wasn't found and can't submit" << std::endl;
		return false;
	}

	std::vector<char> midiBuffer;
	if (uploadMIDI(t_fileMidiPath, midiBuffer) == false)
	{
		std::cerr << "[DB] Midi can't be read and can't submit" << std::endl;
		return false;
	}

	// Inseet
	SQLAllocHandle(SQL_HANDLE_STMT, handleDbc, &handleStatement);

	std::string insertQuery = "INSERT INTO results (user_id, song_id, score, early_notes, perfect_notes, late_notes, missed_notes, wrong_notes, midi_file) "
							  "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)";

	//SQLRETURN returnExecCheck = SQLExecDirectA(handleStatement, (SQLCHAR*)insertQuery.c_str(), SQL_NTS);

	// SQLPrepareA -> Send to databse and see if it's correct but don't push it
	SQLRETURN returnExecCheck = SQLPrepareA(handleStatement, (SQLCHAR*)insertQuery.c_str(), SQL_NTS);
	if (returnExecCheck != SQL_SUCCESS && returnExecCheck != SQL_SUCCESS_WITH_INFO)
	{
		std::cerr << "[DB] Insert results unsuccessful" << std::endl;
		SQLFreeHandle(SQL_HANDLE_STMT, handleStatement); // Free only this handle and not the connection
		return false;
	}

	// Bind
	SQLLEN midiSize = midiBuffer.size();

	//SQLRETURN SQL_API SQLBindParameter(
	//	SQLHSTMT           hstmt,
	//	SQLUSMALLINT       ipar,
	//	SQLSMALLINT        fParamType,
	//	SQLSMALLINT        fCType,
	//	SQLSMALLINT        fSqlType,
	//	SQLULEN            cbColDef,
	//	SQLSMALLINT        ibScale,
	//	SQLPOINTER         rgbValue,
	//	SQLLEN             cbValueMax,
	//	SQLLEN * pcbValue);

	SQLBindParameter(handleStatement, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &userID, 0, NULL);
	SQLBindParameter(handleStatement, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &songID, 0, NULL);

	SQLBindParameter(handleStatement, 3, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &t_stats.m_score, 0, NULL);
	SQLBindParameter(handleStatement, 4, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &t_stats.m_earlyNotes, 0, NULL);
	SQLBindParameter(handleStatement, 5, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &t_stats.m_perfectNotes, 0, NULL);
	SQLBindParameter(handleStatement, 6, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &t_stats.m_lateNotes, 0, NULL);
	SQLBindParameter(handleStatement, 7, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &t_stats.m_missedNotes, 0, NULL);
	SQLBindParameter(handleStatement, 8, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &t_stats.m_wrongNotes, 0, NULL);

	SQLBindParameter(handleStatement, 9, SQL_PARAM_INPUT, SQL_C_BINARY, SQL_VARBINARY, midiSize, 0, midiBuffer.data(), midiSize, &midiSize);

	// Push
	//returnExecCheck = SQLExecDirectA
	returnExecCheck = SQLExecute(handleStatement);
	if (returnExecCheck != SQL_SUCCESS && returnExecCheck != SQL_SUCCESS_WITH_INFO)
	{
		std::cerr << "[DB] Insert results unsuccessful after binding" << std::endl;
		SQLFreeHandle(SQL_HANDLE_STMT, handleStatement); 
		return false;
	}

	std::cerr << "[DB] Insert results successful after binding" << std::endl;
	SQLFreeHandle(SQL_HANDLE_STMT, handleStatement);
	return true;
}

int Database::getSongID(const std::string& t_songName)
{
	std::cerr << "[DB] Looking for song: " << t_songName << std::endl;

	SQLAllocHandle(SQL_HANDLE_STMT, handleDbc, &handleStatement);

	std::string query = "SELECT id FROM songs WHERE song_name = '" + t_songName + "'";
	SQLRETURN returnExecCheck = SQLExecDirectA(handleStatement, (SQLCHAR*)query.c_str(), SQL_NTS);

	if (returnExecCheck != SQL_SUCCESS && returnExecCheck != SQL_SUCCESS_WITH_INFO)
	{
		// Add this block to see the actual error
		SQLCHAR sqlState[6];
		SQLINTEGER nativeError;
		SQLCHAR messageText[SQL_MAX_MESSAGE_LENGTH];
		SQLSMALLINT textLength;

		SQLGetDiagRecA(SQL_HANDLE_STMT, handleStatement, 1, sqlState, &nativeError, messageText, SQL_MAX_MESSAGE_LENGTH, &textLength);
		std::cerr << "[DB] SQLState: " << sqlState << std::endl;
		std::cerr << "[DB] Error: " << messageText << std::endl;

		std::cerr << "[DB] Get song ID unsuccessful" << std::endl;
		SQLFreeHandle(SQL_HANDLE_STMT, handleStatement); // Free only this handle and not the connection
		return -1;
	}

	int songID = -1;
	SQLBindCol(handleStatement, 1, SQL_C_LONG, &songID, sizeof(songID), NULL);

	if (SQLFetch(handleStatement) == SQL_SUCCESS)
	{
		std::cerr << "[DB] Found a song id: " << songID << " for song: " << t_songName << std::endl;
	}
	else
	{
		std::cerr << "[DB] Song not found: " << t_songName << std::endl;
	}

	SQLFreeHandle(SQL_HANDLE_STMT, handleStatement);
	return songID;
}

int Database::getUserID(const std::string& t_username)
{
	SQLAllocHandle(SQL_HANDLE_STMT, handleDbc, &handleStatement);

	std::string query = "SELECT id FROM users WHERE username = '" + t_username + "'";
	SQLRETURN returnExecCheck = SQLExecDirectA(handleStatement, (SQLCHAR*)query.c_str(), SQL_NTS);

	if (returnExecCheck != SQL_SUCCESS && returnExecCheck != SQL_SUCCESS_WITH_INFO)
	{
		std::cerr << "[DB] Get user ID unsuccessful" << std::endl;
		SQLFreeHandle(SQL_HANDLE_STMT, handleStatement); // Free only this handle and not the connection
		return -1;
	}

	int userID = -1;
	SQLBindCol(handleStatement, 1, SQL_C_LONG, &userID, sizeof(userID), NULL);

	if (SQLFetch(handleStatement) == SQL_SUCCESS)
	{
		std::cerr << "[DB] Found a user id: " << userID << " for user: " << t_username << std::endl;
		SQLFreeHandle(SQL_HANDLE_STMT, handleStatement);
		return userID;
	}
	else
	{
		std::cerr << "[DB] User not found so insert: " << t_username << std::endl;
		SQLFreeHandle(SQL_HANDLE_STMT, handleStatement);
		SQLAllocHandle(SQL_HANDLE_STMT, handleDbc, &handleStatement);

		// Insert
		std::string insertQuery = "INSERT INTO users (username) VALUES ('" + t_username + "')";
		SQLExecDirectA(handleStatement, (SQLCHAR*)insertQuery.c_str(), SQL_NTS);

		// Get
		SQLFreeHandle(SQL_HANDLE_STMT, handleStatement);
		SQLAllocHandle(SQL_HANDLE_STMT, handleDbc, &handleStatement);
		std::string selectQuery = "SELECT TOP 1 id FROM users ORDER BY id DESC";
		SQLExecDirectA(handleStatement, (SQLCHAR*)selectQuery.c_str(), SQL_NTS);

		SQLBindCol(handleStatement, 1, SQL_C_LONG, &userID, sizeof(userID), NULL);
		SQLFetch(handleStatement);

		std::cerr << "Inserted user with ID of: " << userID << std::endl;
		SQLFreeHandle(SQL_HANDLE_STMT, handleStatement);
		return userID;
	}
	//return userID;
}

bool Database::uploadMIDI(std::string& t_filePath, std::vector<char>& t_outputBuffer)
{
	std::ifstream file(t_filePath, std::ifstream::in | std::ios::binary);

	if (!file.is_open())
	{
		std::cerr << "[DB] Couldn't open the file path at: " << t_filePath << std::endl;
		return false;
	}

	// File size
	file.seekg(0, std::ios::end);
	std::streamsize fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	t_outputBuffer.resize(fileSize);
	file.read(t_outputBuffer.data(), fileSize);

	if (file)
	{
		std::cerr << "[DB] Midi read successful: " << fileSize << std::endl;
	}
	else
	{
		std::cerr << "[DB] Midi read unsuccessful: " << std::endl;
		return false;
	}

	file.close();
	return true;
}

void Database::SQLCleanup(/*SQLHENV& t_handleEnvir, SQLHDBC& t_handleDbc, SQLHSTMT& t_handleStatement*/)
{
	SQLFreeHandle(SQL_HANDLE_STMT, handleStatement);
	SQLDisconnect(handleDbc);
	SQLFreeHandle(SQL_HANDLE_DBC, handleDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, handleEnvir);
	bool b_isConnected = false;
}

bool Database::getConnectionStatus()
{
	return b_isConnected;
}
