#include "harness.h"
#include <QTime>
#include "guipacket.h"
#include "helperfunctions.h"

#define SYSTEM_TIMER_INTERVAL_MS 500
#define MAX_PACKET_INTERVAL_MS 1200

Harness::Harness(QObject *parent) : QObject(parent)
{
	gui = new MainWindow;
	serialManager = new SerialManager;
	packetReceiver = new PacketReceiver;
	windDataAnalyzer = new WindDataAnalyzer;
	dataLogger = new DataLogger;
	systemTimer = new QTimer;
	batteryChargeCalculator = new BatteryChargeCalculator;
	loggingData = false;

	connect(serialManager, SIGNAL(onNewDataReady(QByteArray)), packetReceiver, SLOT(onNewDataReceived(QByteArray)));
	connect(serialManager, SIGNAL(serialPortError(QString)), this, SLOT(onSerialPortError(QString)));
	connect(packetReceiver, SIGNAL(validPacketReceived()), this, SLOT(onValidPacketReceived()));
	connect(packetReceiver, SIGNAL(invalidPacketReceived()), this, SLOT(onInvalidPacketReceived()));
	connect(gui, SIGNAL(connectSerialButtonClicked(QString)), this, SLOT(onConnectSerialButtonClicked(QString)));
	connect(gui, SIGNAL(saveDataLogButtonClicked()), this, SLOT(onSaveDataLogButtonClicked()));
	connect(gui, SIGNAL(startLoggingButtonClicked()), this, SLOT(onStartLoggingButtonClicked()));
	connect(gui, SIGNAL(clearLogButtonClicked()), this, SLOT(onClearLogButtonClicked()));
	connect(gui, SIGNAL(settingsChanged()), this, SLOT(onSettingsChanged()));
	connect(systemTimer, SIGNAL(timeout()), this, SLOT(onSystemTimerTimeout()));

	loadGUIDefaultValues();
	gui->show();
	systemTimer->start(SYSTEM_TIMER_INTERVAL_MS);
}

void Harness::onSystemTimerTimeout()
{
	int lastValidPacketTimestamp = packetReceiver->getLastValidPacketTimestamp();
	int dt = QTime::currentTime().msecsSinceStartOfDay() - lastValidPacketTimestamp;
	if(dt > MAX_PACKET_INTERVAL_MS) {
		gui->setReceivingDataIcon(false);
	}
}

void Harness::onValidPacketReceived()
{
	Packet packet = packetReceiver->getPacket();
	//printPacket(packet);
	windDataAnalyzer->addNewWindSpeed(packet.getWindSpeed());
	GUIPacket guiPacket(packet);
	guiPacket.setCompassOffset(compassOffset);
	guiPacket.setAverageWindSpeed(windDataAnalyzer->getAverageSpeed());
	guiPacket.setGustSpeed(windDataAnalyzer->getGustSpeed());
	double batteryCharge = batteryChargeCalculator->getCharge(packet.getBatteryVoltage() / 2);
	guiPacket.setBatteryCharge(batteryCharge);
	guiPacket.setBatteryTimeLeft(batteryCharge / 100.0 * 28.6);
	gui->updateGUI(guiPacket);
	gui->setReceivingDataIcon(true);
	if(loggingData) {
		dataLogger->appendData(guiPacket);
		gui->appendDataLog(dataLogger->getNewestLine());
	}
}

void Harness::onInvalidPacketReceived()
{
	//TODO
}

void Harness::onConnectSerialButtonClicked(QString portName)
{
	if(!serialManager->isConnected()) {
		if(!serialManager->connectToSerialPort(portName)) {
			qDebug() << "Harness::onConnectSerialButtonClicked: unable to connect to serial port " << portName;
		} else {
			qDebug() << "Harness::onConnectSerialButtonClicked: connected to serial port " << portName;
			gui->setSerialConnected();
		}
	} else {
		qDebug() << "Harness::onConnectSerialButtonClicked: disconnecting from serial port";
		serialManager->disconnectFromSerialPort();
		gui->setSerialConnected(false);
	}
}

void Harness::onStartLoggingButtonClicked()
{
	if(loggingData) {
		loggingData = false;
		gui->setLogging(false);
		return;
	}
	loggingData = true;
	gui->setLogging();
}

void Harness::onSaveDataLogButtonClicked()
{
	QString filePath = gui->getSaveLogFilePath();
	if(filePath.isEmpty()) {
		qDebug() << "Harness::onSaveDataLogButtonClicked(): empty file path";
		return;
	}
	dataLogger->saveToFile(filePath);
}

void Harness::onClearLogButtonClicked()
{
	gui->clearDataLog();
	dataLogger->clearLog();
}

void Harness::onSerialPortError(QString errorMessage)
{
	qDebug() << "Harness::onSerialPortError() : " << errorMessage;
	//TODO
}

void Harness::onSettingsChanged()
{
	qDebug() << "Harness::onSettingsChanged()";
	windDataAnalyzer->setAverageSpeedCalculationTimeRange(gui->getAverageSpeedCalculationTimeRange());
	windDataAnalyzer->setGustSpeedCalculationTimeRange(gui->getGustSpeedCalculationTimeRange());
	dataLogger->enableAutomaticSaving(gui->getAutomaticLogSavingEnabled());
	dataLogger->setAutomaticSavingInterval(gui->getAutomaticLogSavingIntervalS());
	dataLogger->setAutomaticSavingFolderPath(gui->getAutomaticLogSavingFolderPath());
	compassOffset = gui->getCompassOffset();
}

void Harness::loadGUIDefaultValues()
{
	Packet packet;
	packet.setAccelerometerErrorFlag();
	packet.setAnemometerErrorFlag();
	packet.setBarometerErrorFlag();
	packet.setBatteryErrorFlag();
	packet.setMagnetometerErrorFlag();
	packet.setWindVaneErrorFlag();
	GUIPacket guiPacket(packet);
	guiPacket.setBatteryTimeLeft(0);
	gui->updateGUI(guiPacket);
}
