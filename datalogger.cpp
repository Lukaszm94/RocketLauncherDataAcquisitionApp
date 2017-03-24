#include "datalogger.h"
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include "settingsmanager.h"

extern SettingsManager settingsManager;

DataLogger::DataLogger(QObject *parent) : QObject(parent)
{
	automaticSaveTimer = new QTimer;
	automaticSavingEnabled = settingsManager.getSettings().automaticLogSavingEnabled;
	automaticSavingIntervalS = settingsManager.getSettings().automaticLogSavingIntervalS;
	automaticSaveTimer->setInterval(settingsManager.getSettings().automaticLogSavingIntervalS * 1000);

	enableAutomaticSaving(automaticSavingEnabled);
	connect(automaticSaveTimer, SIGNAL(timeout()), this, SLOT(onAutomaticSaveTimerTimeout()));
}

void DataLogger::clearLog()
{
	buffer.clear();
}

void DataLogger::appendData(GUIPacket packet)
{
	QString timeStr = packet.getReceivedTimeStr();
	QString railAngleStr = packet.getRailAngle(false);
	QString orientationStr = packet.getNorthAngle(false);
	QString actualWindSpeedStr = packet.getActualWindSpeedStr(false);
	QString averageWindSpeedStr = packet.getAverageWindSpeedStr(false);
	QString gustSpeedStr = packet.getGustSpeedStr(false);
	QString windDirectionStr = packet.getWindDirection();
	QString pressureStr = packet.getPressure(false);
	QString temperatureStr = packet.getTemperature(false);
	//QString batteryVoltageStr = packet.getBatteryVoltage(false);
	newestLine = timeStr + "," + railAngleStr + "," + orientationStr + "," + actualWindSpeedStr + "," + averageWindSpeedStr + "," + gustSpeedStr + "," + windDirectionStr + "," + pressureStr + "," + temperatureStr;
	buffer += newestLine + '\n';
}

QString DataLogger::getNewestLine()
{
	return newestLine;
}

bool DataLogger::saveToFile(QString filePath)
{
	return saveBufferToFile(filePath, buffer);
}

bool DataLogger::saveBufferToFile(QString filePath, QString buff)
{
	QFile file;
	file.setFileName(filePath);
	if(!file.open(QFile::WriteOnly)) {
		qDebug() << "DataLogger::saveToFile(): saving failed, could not open file " << filePath;
		return false;
	}
	QTextStream stream(&file);
	QString header;
	header = "Date[h:m:s],railAngle[deg],orientationAngle[deg],measuredWindSpeed[m/s],averageWindSpeed[m/s],gustSpeed[m/s],windDirection,pressure[hPa],temperature[degC]";
	stream << header << '\n';
	stream << buff;
	file.close();
	return true;
}

void DataLogger::enableAutomaticSaving(bool enable)
{
	automaticSavingEnabled = enable;
	if(automaticSavingEnabled) {
		automaticSaveTimer->start();
	} else {
		automaticSaveTimer->stop();
	}

}

void DataLogger::setAutomaticSavingFolderPath(QString path)
{
	automaticSavingFolderPath = path;
}

void DataLogger::setAutomaticSavingInterval(int intervalS)
{
	automaticSavingIntervalS = intervalS;
	automaticSaveTimer->setInterval(automaticSavingIntervalS * 1000);
}

void DataLogger::onAutomaticSaveTimerTimeout()
{
	qDebug() << "DataLogger::onAutomaticSaveTimerInterrupt()";
	QString fileName = "log_autosave_" + QTime::currentTime().toString() + ".csv";
	fileName.replace(':', '_');
	QString fullPath = automaticSavingFolderPath;
	if(!automaticSavingFolderPath.isEmpty()) {
		fullPath += "/";
	}
	fullPath += fileName;
	qDebug() << "File with pathname: " << fullPath;
	if(saveBufferToFile(fullPath, buffer)) {
		qDebug() << "Automatic save OK";
	} else {
		qDebug() << "Automatic save failed";
	}
}
