#include "mainwindow.h"
#include <QApplication>
#include "harness.h"
#include "settingsmanager.h"

SettingsManager settingsManager;

int main(int argc, char *argv[])
{
	settingsManager.loadSavedSettings();
	QApplication a(argc, argv);
	Harness* harness = new Harness;

	return a.exec();
}
