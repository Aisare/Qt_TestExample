#ifndef SummatorsVectorClassH
#define SummatorsVectorClassH

#include <mutex>
#include <vector>
#include <algorithm>
#include <QTableWidget>
#include <QLabel>

#include "SummatorClass.h"
#include "SQLiteApi.h"
#include "ConstantsSQL.h"

/// <summary>
/// SummatorsVector - class thread-safe vector of Summator
/// </summary>
class SummatorsVector : public QObject
{
	Q_OBJECT
private:
	//Mutex to ensure thread-safety when accessing or modifying the data
	std::mutex lock_mutex;
	//Vector containing unique pointers to Summator
	std::vector<std::unique_ptr<Summator>> summators;
	//Pointer to the QTableWidget
	QTableWidget* ptr_table = nullptr;
	//SQLiteApi - database for storing Summators data
	SQLiteApi dataBase;

public:
	/// <summary>
	/// Default constructor
	/// </summary>
	SummatorsVector() = default;
	/// <summary>
	/// Sets the QTableWidget pointer
	/// </summary>
	/// <param name="table">The pointer to the QTableWidget</param>
	void SetPtrTable(QTableWidget* table);
	/// <summary>
	/// Adds a new Summator to the vector and QTableWidget
	/// </summary>
	/// <param name="defaultvalue">The initial value for the new Summator</param>
	void Add(int64_t defaultvalue = 0);
	/// <summary>
	/// Removes the Summator at the index
	/// </summary>
	/// <param name="index">The index of the Summator to be removed</param>
	void Remove(int index);
	/// <summary>
	/// Increments all the Summators
	/// </summary>
	void Increment();

	/// <summary>
	/// Connects to a database 
	/// </summary>
	/// <param name="db_name">The path to the database file</param>
	void ConnectToDB(const std::string& db_name);
	/// <summary>
	/// Saves the current Summators data to the connected database
	/// </summary>
	void SaveDataToDB();
	/// <summary>
	/// Loads the Summators data from the connected database and added in the QTableWidget
	/// </summary>
	void LoadDataToDB();

signals:
	/// <summary>
	/// Signal emitted when the frequency
	/// </summary>
	void FrequencyUpdate(double newHz);
};

#endif //SummatorsVectorClassH