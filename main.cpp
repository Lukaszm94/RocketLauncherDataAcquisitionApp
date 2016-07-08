#include "mainwindow.h"
#include <QApplication>
#include "harness.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Harness* harness = new Harness;

	return a.exec();
}
