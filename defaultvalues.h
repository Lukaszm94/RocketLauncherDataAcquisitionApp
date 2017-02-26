#ifndef DEFAULTVALUES_H
#define DEFAULTVALUES_H
#include <QString>

class DefaultValues
{
public:
	DefaultValues();
	static int getAverageSpeedCalculationTimeRange();
	static int getGustSpeedCalculationTimeRange();
	static int getAutomaticLogSavingIntervalS();
	static bool getAutomaticLogSavingEnabled();
	static QString getAutomaticLogSavingFolderPath();

	static double getCompassOffset();
};

#endif // DEFAULTVALUES_H
