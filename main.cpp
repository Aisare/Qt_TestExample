#include <QApplication>
#include "QtWidgets_MainForm.h"

void main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	
	std::string pathDB = "test.db";
	
	QtWidgets_MainForm mainForm(pathDB);
	mainForm.show();
	
	app.exec();
	return;
}