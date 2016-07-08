#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "timeplotwidget.h"
#include "connectiontabwidget.h"
#include "datadisplaywidget.h"
#include "statuswidget.h"
#include "dataloggingwidget.h"
#include "guipacket.h"
#include "settingswidget.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	void updateGUI(GUIPacket guiPacket);
	void appendDataLog(QString str);
	void clearDataLog();
	void setSerialConnected(bool connected = true);
	void setReceivingDataIcon(bool receiving);
	void setLogging(bool loggingEnabled = true);
	int getAverageSpeedCalculationTimeRange();
	int getGustSpeedCalculationTimeRange();
	bool getAutomaticLogSavingEnabled();
	int getAutomaticLogSavingIntervalS();
	QString getAutomaticLogSavingFolderPath();
	QString getSaveLogFilePath();
	double getCompassOffset();

private slots:
	void onConnectSerialButtonClicked(QString portName);
	void onSaveDataLogButtonClicked();
	void onStartLoggingButtonClicked();
	void onClearLogButtonClicked();
	void onSettingsChanged();

signals:
	void connectSerialButtonClicked(QString portName);
	void startLoggingButtonClicked();
	void saveDataLogButtonClicked();
	void clearLogButtonClicked();
	void settingsChanged();



private:
	QTabWidget *tabWidget;
	QLabel* batteryTimeLeftLabel;
	QLabel* skaLogoLabel;
	QLabel* sectionLogoLabel;
	ConnectionTabWidget* connectionTabWidget;
	DataDisplayWidget* dataDisplayWidget;
	DataLoggingWidget* dataLoggingWidget;
	StatusWidget* statusWidget;
	SettingsWidget* settingsWidget;

	QHBoxLayout* topLayout;
	QVBoxLayout* mainLayout;
	QWidget* centralWidget;
};

#endif // MAINWINDOW_H
