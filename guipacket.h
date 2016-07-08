#ifndef GUIPACKET_H
#define GUIPACKET_H

#include <QString>
#include <QTime>
#include "packet.h"

class GUIPacket
{
public:
	GUIPacket(Packet packet_);

	QString getLatitude();
	QString getLongitude();
	QString getRailAngle(bool unit = true);
	QString getNorthAngle(bool unit = true);
	QString getActualWindSpeedStr(bool unit = true);
	QString getAverageWindSpeedStr(bool unit = true);
	QString getGustSpeedStr(bool unit = true);
	QString getWindDirection();
	QString getPressure(bool unit = true);
	QString getTemperature(bool unit = true);
	QString getBatteryStateStr(bool unit = true);
	//QString getWeatherStationErrors();
	QString getGPSFixAge();
	QString getGPSFailedSentencesCount();
	QString getGPSSatellitesCount();
	QString getGPSFixDetected();
	QString getPacketsCountData();
	QString getReceivedTimeStr();
	QString getReceivedTimeMsStr();
	float getAverageWindSpeed();
	float getGustSpeed();
	float getCurrentWindSpeed();
	float getBatteryVoltage();
	int getMagneticNorthCompassData(); // functions used to get data used to set compass' needle angle
	int getWindDirectionCompassData();
	void setAverageWindSpeed(float value);
	void setGustSpeed(float value);
	void setBatteryCharge(double charge);
	void setBatteryTimeLeft(int time);
	void setValidPacketsCount(int value);
	void setInvalidPacketsCount(int value);
	bool isBarometerErrorFlagSet();
	bool isMagnetometerErrorFlagSet();
	bool isAccelerometerErrorFlagSet();
	bool isAnemometerErrorFlagSet();
	bool isWindVaneErrorFlagSet();
	bool isBatteryErrorFlagSet();
	bool isGPSFixDetected();
	void setCompassOffset(double offset);

private:
	QString generateString(float value, int precision, QString unit = "");
	QString generateString(int value, QString unit = "");

	Packet packet;
	float gustSpeed;
	float averageWindSpeed;
	double batteryCharge; // in percent
	int batteryTimeLeft; // in hours
	double compassOffset;
	int validPacketsCount;
	int invalidPacketsCount;
	QTime lifeStartTime;
};

#endif // GUIPACKET_H
