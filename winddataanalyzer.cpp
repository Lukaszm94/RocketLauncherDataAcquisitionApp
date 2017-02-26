#include "winddataanalyzer.h"
#include <QDebug>
#include "defaultvalues.h"
#include "settingsmanager.h"

extern SettingsManager settingsManager;

WindDataAnalyzer::WindDataAnalyzer()
{
	time.start();
	averageSpeedCalculationTimeRange = settingsManager.getSettings().averageSpeedCalculationTimeRange;
	gustSpeedCalculationTimeRange = settingsManager.getSettings().gustSpeedCalculationTimeRange;
}

void WindDataAnalyzer::addNewWindSpeed(float speed)
{
	WindSpeedMeasurement measurement;
	measurement.speed = speed;
	measurement.timestamp = getCurrentTime();
	buffer.append(measurement);
}

float WindDataAnalyzer::getGustSpeed()
{
	int oldestMeasurementTime = getCurrentTime() - gustSpeedCalculationTimeRange;
	float maxSpeed = 0.0;
	QVectorIterator<WindSpeedMeasurement> i(buffer);
	i.toBack();
	while(i.hasPrevious()) {
		WindSpeedMeasurement measurement = i.previous();
		if(measurement.timestamp < oldestMeasurementTime) {
			break;
		}
		if(measurement.speed > maxSpeed) {
			maxSpeed = measurement.speed;
		}
	}
	return maxSpeed;
}

float WindDataAnalyzer::getAverageSpeed()
{
	int oldestMeasurementTime = getCurrentTime() - averageSpeedCalculationTimeRange;
	float speedSum = 0;
	int summedCount = 0;
	QVectorIterator<WindSpeedMeasurement> i(buffer);
	i.toBack();
	while(i.hasPrevious()) {
		WindSpeedMeasurement measurement = i.previous();
		if(measurement.timestamp < oldestMeasurementTime) {
			break;
		}
		speedSum += measurement.speed;
		summedCount++;
	}
	if(summedCount == 0) {
		return 0;
	}
	return speedSum / summedCount;
}

void WindDataAnalyzer::setAverageSpeedCalculationTimeRange(int time)
{
	averageSpeedCalculationTimeRange = time;
}

void WindDataAnalyzer::setGustSpeedCalculationTimeRange(int time)
{
	gustSpeedCalculationTimeRange = time;
}

int WindDataAnalyzer::getCurrentTime()
{
	return (time.elapsed() / 1000);
}
