#include "guipacket.h"
#include <QDebug>
#include "defaultvalues.h"


GUIPacket::GUIPacket(Packet packet_)
{
	gustSpeed = averageWindSpeed = 0.0;
	validPacketsCount = invalidPacketsCount = 0;
	batteryCharge = 0.0;
	batteryTimeLeft = 0;
	compassOffset = DefaultValues::getCompassOffset();
	packet = packet_;
	lifeStartTime = QTime::currentTime();
}

QString GUIPacket::getLatitude()
{
	float latitude = packet.getLatitude();
	latitude /= 1000000;
	QString letter = "N";
	if(latitude < 0.0) {
		latitude = -latitude;
		letter = "S";
	}

	QString latitudeStr = QString::number(latitude, 'f');
	return letter + latitudeStr;
}

QString GUIPacket::getLongitude()
{
	double longitude = packet.getLongitude();
	longitude /= 1000000;
	QString letter = "E";
	if(longitude < 0.0) {
		longitude = -longitude;
		letter = "W";
	}
	QString longitudeStr = generateString(longitude, 6);
	return letter + longitudeStr;
}

QString GUIPacket::getRailAngle(bool unit)
{
	QString unitStr = "";
	if(unit) {
		unitStr = "°";
	}
	return generateString(packet.getRailAngle(), 1, unitStr);
}

QString GUIPacket::getNorthAngle(bool unit)
{
	QString unitStr = "";
	if(unit) {
		unitStr = "°";
	}
	double value = packet.getMagneticNorthAngle();
	value += compassOffset;
	if(value > 360.0) {
		value -= 360.0;
	}
	if(value < 0.0) {
		value += 360.0;
	}
	return generateString(value, 1, unitStr);
}

QString GUIPacket::getActualWindSpeedStr(bool unit)
{
	QString unitStr = "";
	if(unit) {
		unitStr = "m/s";
	}
	return generateString(packet.getWindSpeed(), 1, unitStr);
}

QString GUIPacket::getAverageWindSpeedStr(bool unit)
{
	QString unitStr = "";
	if(unit) {
		unitStr = "m/s";
	}
	return generateString(averageWindSpeed, 1, unitStr);
}

QString GUIPacket::getGustSpeedStr(bool unit)
{
	QString unitStr = "";
	if(unit) {
		unitStr = "m/s";
	}
	return generateString(gustSpeed, 1, unitStr);
}

QString GUIPacket::getWindDirection()
{
	QString directions[] = {"N", "NE", "E", "SE", "S", "SW", "W", "NW"};
	int directionIndex = (int) packet.getWindDirection();
	//qDebug() << "GUIPacket::getWindDirection(): direction index: " << directionIndex;
	if(directionIndex > sizeof(directions) || directionIndex < 0) {
		qDebug() << "GUIPacket::getWindDirection(): wrong direction index= " << directionIndex;
		directionIndex = 0;
	}
	return directions[directionIndex];
	//TODO what about compass offset?
}

QString GUIPacket::getPressure(bool unit)
{
	QString unitStr = "";
	if(unit) {
		unitStr = "hPa";
	}
	return generateString(packet.getPressure(), 1, unitStr);
}

QString GUIPacket::getTemperature(bool unit)
{
	QString unitStr = "";
	if(unit) {
		unitStr = "°C";
	}
	return generateString(packet.getTemperature(), 1, unitStr);
}

QString GUIPacket::getBatteryStateStr(bool unit)
{
	QString unitStr = "";
	if(unit) {
		unitStr = "V";
	}
	QString str = generateString(packet.getBatteryVoltage(), 2, unitStr);
	str += " (" + QString::number(batteryCharge,'f', 0) + "%, approx. " + QString::number(batteryTimeLeft) + "h left)";
	return str;
}

/*QString GUIPacket::getWeatherStationErrors()
{
	return ""; //TODO what to return?
}*/

QString GUIPacket::getGPSFixAge()
{
	return generateString(packet.getGPSFixAge(), "s");
}

QString GUIPacket::getGPSFailedSentencesCount()
{
	return generateString(packet.getGPSFailedSentencesCount());
}

QString GUIPacket::getGPSSatellitesCount()
{
	return generateString(packet.getGPSSatellitesCount());
}

QString GUIPacket::getGPSFixDetected()
{
	if(packet.getGPSFixDetected()) {
		return "Fix detected";
	} else {
		return "Fix NOT detected";
	}
}

QString GUIPacket::getPacketsCountData()
{
	int packetsSum = validPacketsCount + invalidPacketsCount;
	QString str = generateString(packetsSum) + " received (" + generateString(validPacketsCount) + " valid and " + generateString(invalidPacketsCount) + " invalid)";
	return str;
}

QString GUIPacket::getReceivedTimeStr()
{
	return lifeStartTime.toString();
}

QString GUIPacket::getReceivedTimeMsStr()
{
	return QString::number(lifeStartTime.msecsSinceStartOfDay() / 1000);
}

float GUIPacket::getAverageWindSpeed()
{
	return averageWindSpeed;
}

float GUIPacket::getGustSpeed()
{
	return gustSpeed;
}

float GUIPacket::getCurrentWindSpeed()
{
	return packet.getWindSpeed();
}

float GUIPacket::getBatteryVoltage()
{
	return packet.getBatteryVoltage();
}

int GUIPacket::getMagneticNorthCompassData()
{
	//TODO
}

int GUIPacket::getWindDirectionCompassData()
{
	//TODO
}

void GUIPacket::setAverageWindSpeed(float value)
{
	averageWindSpeed = value;
}

void GUIPacket::setGustSpeed(float value)
{
	gustSpeed = value;
}

void GUIPacket::setBatteryCharge(double charge)
{
	batteryCharge = charge;
}

void GUIPacket::setBatteryTimeLeft(int time)
{
	batteryTimeLeft = time;
}

void GUIPacket::setValidPacketsCount(int value)
{
	validPacketsCount = value;
}

void GUIPacket::setInvalidPacketsCount(int value)
{
	invalidPacketsCount = value;
}

bool GUIPacket::isBarometerErrorFlagSet()
{
	return packet.isBarometerErrorFlagSet();
}

bool GUIPacket::isMagnetometerErrorFlagSet()
{
	return packet.isMagnetometerErrorFlagSet();
}

bool GUIPacket::isAccelerometerErrorFlagSet()
{
	return packet.isAccelerometerErrorFlagSet();
}

bool GUIPacket::isAnemometerErrorFlagSet()
{
	return packet.isAnemometerErrorFlagSet();
}

bool GUIPacket::isWindVaneErrorFlagSet()
{
	return packet.isWindVaneErrorFlagSet();
}

bool GUIPacket::isBatteryErrorFlagSet()
{
	return packet.isBatteryErrorFlagSet();
}

bool GUIPacket::isGPSFixDetected()
{
	return packet.getGPSFixDetected();
}

void GUIPacket::setCompassOffset(double offset)
{
	compassOffset = offset;
}

QString GUIPacket::generateString(float value, int precision, QString unit)
{
	if(precision < 0) {
		precision = 1;
	}
	QString valueStr = QString::number(value, 'f', precision);
	return valueStr + unit;
}

QString GUIPacket::generateString(int value, QString unit)
{
	QString valueStr = QString::number(value);
	return valueStr + unit;
}
