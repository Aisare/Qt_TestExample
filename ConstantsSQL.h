#ifndef CONSTANTSSQLH
#define CONSTANTSSQLH

/// <summary>
/// Constants for SQL requests
/// </summary>

static const char* CreatTableSQL = "CREATE TABLE IF NOT EXISTS SummatorData \
								(id INTEGER PRIMARY KEY, value INTEGER);";

static const char* DeleteDataSQL = "DELETE FROM SummatorData;";
static const char* InsertDataSQL = "INSERT INTO SummatorData (value) VALUES";
static const char* ReadDataSQL = "SELECT value FROM SummatorData;";

#endif//CONSTANTSSQLH