#ifndef WINDDATAANALYZER_H
#define WINDDATAANALYZER_H

#include <QTime>
#include <QVector>

struct WindSpeedMeasurement
{
	float speed;
	int timestamp; // in seconds
};

class WindDataAnalyzer
{
public:
	WindDataAnalyzer();
	void addNewWindSpeed(float speed);
	float getGustSpeed();
	float getAverageSpeed();
	void setAverageSpeedCalculationTimeRange(int time);
	void setGustSpeedCalculationTimeRange(int time);
private:
	int getCurrentTime();
	int averageSpeedCalculationTimeRange;
	int gustSpeedCalculationTimeRange;

	QTime time;
	QVector<WindSpeedMeasurement> buffer;
};

#endif // WINDDATAANALYZER_H
