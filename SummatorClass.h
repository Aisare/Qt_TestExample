#ifndef SummatorClassH
#define SummatorClassH

#include <QObject>
#include <atomic>
#include <QTableWidget>

/// <summary>
/// Summator - class is a thread-safe adder
/// </summary>
class Summator : public QObject
{
	Q_OBJECT
private:
	//Atomic variable to store the sum, ensuring thread-safety
	std::atomic<int64_t> summ{ 0 };
	//The row index in the QTableWidget
	int rowTable = -1;
	//Pointer to the QTableWidget
	QTableWidget* ptrTable = nullptr;
public:
	/// <summary>
	/// Default constructor
	/// </summary>
	Summator() = default;
	/// <summary>
	/// Increases the value of the Summator by 1
	/// </summary>
	void Increment();
	/// <summary>
	/// Retrieves the current sum stored in the Summator
	/// </summary>
	/// <returns>the curent summ</returns>
	int64_t GetSumm();
	/// <summary>
	/// Sets the value of the Summator
	/// </summary>
	/// <param name="value">The value to set for the summ</param>
	void SetSumm(int64_t value);
	/// <summary>
	/// Sets the row index for the QTableWidget
	/// </summary>
	/// <param name="newRow">The new row index</param>
	void SetRow(int newRow);
	/// <summary>
	/// Sets the QTableWidget pointer
	/// </summary>
	/// <param name="table">The pointer to the QTableWidget</param>
	void SetTable(QTableWidget* table);
	/// <summary>
	/// Updates the data in the table with a new value
	/// </summary>
	/// <param name="newData">The new value to be displayed in the QTableWidget</param>
	void UpdateData(int newData);
	/// <summary>
	/// Retrieves the current row index
	/// </summary>
	/// <returns>The current row index</returns>
	int GetRow();
signals:
	/// <summary>
	/// Signal emitted whenever the Summator summ changes
	/// </summary>
	void summChanged(int newSumm);
};

#endif // !SummatorClassH
