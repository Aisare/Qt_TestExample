#ifndef SQLiteApiH
#define SQLiteApiH

#include <string>
#include <memory>
#include <vector>
#include <iostream>

#include "sqlite3.h"

/// <summary>
/// SQLiteApi is a mini-class for convenient database management 
/// </summary>
class SQLiteApi
{
public:
	//alias for the vector<vector<string>> 
	//The type representing the result of executing a SELECT query
	using ResultRows = std::vector<std::vector<std::string>>;
private:
	//Database name
	std::string db_name = "";
	//A pointer to an SQLite database object
	sqlite3* dataBase = nullptr;
	//A flag that indicates whether the database is open
	bool is_open_db = false;
public:
	/// <summary>
	/// Default constructor
	/// </summary>
	SQLiteApi() = default;
	/// <summary>
	/// Connects to the database using the path
	/// </summary>
	/// <param name="db_path_name">The path to the database file</param>
	/// <returns>The result of connecting to the database</returns>
	bool connect(const std::string& db_path_name);
	/// <summary>
	/// Closes the current database connection
	/// </summary>
	/// <returns>The result of disconnected to the database</returns>
	bool disconnect();
	/// <summary>
	/// Executes an SQL query
	/// </summary>
	/// <param name="query">SQL query</param>
	/// <param name="params">Request parameters</param>
	/// <returns>The result of the query execution in the form of ResultRows</returns>
	ResultRows Exec(const std::string& query, const std::vector<std::string>& params = {});
};

#endif //SQLiteApiH
