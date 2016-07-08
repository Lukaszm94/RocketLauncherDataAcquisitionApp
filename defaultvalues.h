#ifndef DEFAULTVALUES_H
#define DEFAULTVALUES_H


class DefaultValues
{
public:
	DefaultValues();
	static int getAverageSpeedCalculationTimeRange();
	static int getGustSpeedCalculationTimeRange();
	static int getAutomaticLogSavingIntervalS();
	static bool getAutomaticLogSavingEnabled();
	static double getCompassOffset();
};

#endif // DEFAULTVALUES_H
