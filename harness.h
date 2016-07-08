#ifndef HARNESS_H
#define HARNESS_H

#include <QObject>
#include <QTimer>
#include "mainwindow.h"
#include "serialmanager.h"
#include "packetreceiver.h"
#include "winddataanalyzer.h"
#include "datalogger.h"
#include "batterychargecalculator.h"

class Harness : public QObject
{
	Q_OBJECT
public:
	explicit Harness(QObject *parent = 0);

private slots:
	void onSystemTimerTimeout();

public slots:
	void onValidPacketReceived();
	void onInvalidPacketReceived();
	void onConnectSerialButtonClicked(QString portName);
	void onStartLoggingButtonClicked();
	void onSaveDataLogButtonClicked();
	void onClearLogButtonClicked();
	void onSerialPortError(QString errorMessage);
	void onSettingsChanged();

private:
	void loadGUIDefaultValues();

	MainWindow* gui;
	SerialManager* serialManager;
	PacketReceiver* packetReceiver;
	WindDataAnalyzer* windDataAnalyzer;
	DataLogger* dataLogger;
	QTimer* systemTimer;
	BatteryChargeCalculator* batteryChargeCalculator;
	bool loggingData;
	double compassOffset;
};

#endif // HARNESS_H
