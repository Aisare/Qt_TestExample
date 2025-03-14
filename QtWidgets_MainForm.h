#pragma once

#include <QWidget>
#include "ui_QtWidgets_MainForm.h"

#include <QLabel>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <thread>
#include <memory>

#include "SummatorsVectorClass.h"

/// <summary>
/// QtWidgets_MainForm - represents the main UI form of the application
/// </summary>
class QtWidgets_MainForm : public QWidget
{
	Q_OBJECT
private:
	//Path to the database used for storing and retrieving data
	std::string DBName = "";
	//Pointer to a QLabel used to display the frequency
	QLabel* label = nullptr;
	//Pointer to a QTableWidget used to display data related to Summators
	QTableWidget* table = nullptr;
	//The index of the currently selected row
	int selectedRow = -1;
	//Instance of the SummatorsVector class that manages the collection of Summator
	SummatorsVector summators;
	//Atomic flag indicating if the application is exiting, used for thread safety
	std::atomic<bool> isExitFlag{ false };
	//A unique pointer to the thread responsible for incrementing the Summators
	std::unique_ptr<std::thread> IncrementThread;
	
public:
	/// <summary>
	/// Constructor for QtWidgets_MainForm
	/// </summary>
	/// <param name="pathDB">The path to the database to connect to</param>
	/// <param name="parent">The parent widget</param>
	QtWidgets_MainForm(const std::string &pathDB,QWidget *parent = nullptr);
	/// <summary>
	/// Destructor for QtWidgets_MainForm
	/// </summary>
	~QtWidgets_MainForm();



private:
	//ui: An object containing all the interface elements for the main form
	Ui::QtWidgets_MainFormClass ui;

	/// <summary>
	/// Initializes the user interface components
	/// </summary>
	void Initialization();
	/// <summary>
	/// Loads the Summators data from the database and adding them to QTableWidget
	/// </summary>
	void LoadOnDB();
	/// <summary>
	/// Saves the current Summators data to the database
	/// </summary>
	void SaveOnDB();
	/// <summary>
	/// Runs the incrementing logic in a separate thread
	/// </summary>
	void ThreadIncrement();
	/// <summary>
	/// Adds a new Summator to the SummatorsVector and adding to the QTableWidget
	/// </summary>
	void AddNewSummator();
	/// <summary>
	/// Removes the selected Summator from the SummatorsVector and deletion from the QTableWidget
	/// </summary>
	void RemoveSelectedSummator();

	/// <summary>
	/// Handles the selection of an item (row) in the table and updates the selectedRow
	/// </summary>
	void SelectedItem();
	/// <summary>
	/// Starts the incrementing thread
	/// </summary>
	void StartThread();
	/// <summary>
	/// Stops the incrementing thread
	/// </summary>
	void StopThread();
	/// <summary>
	/// Updates the label with the given frequency value
	/// </summary>
	/// <param name="newHz">The new frequency value to display</param>
	void UpdateLabel(double newHz);
	/// <summary>
	/// Creates a new QPushButton with the given text and connects it to the provided click handler function
	/// </summary>
	/// <param name="buttonText">The text to display</param>
	/// <param name="parent">The parent widget</param>
	/// <param name="onClickFunction">The function to be called when the button is clicked</param>
	/// <returns>A pointer to the created QPushButton</returns>
	QPushButton* CreatButton(const QString& buttonText,QWidget* parent, std::function<void()> onClickFunction);

};
