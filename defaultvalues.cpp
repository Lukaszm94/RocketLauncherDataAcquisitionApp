#include "defaultvalues.h"

DefaultValues::DefaultValues()
{

}

int DefaultValues::getAverageSpeedCalculationTimeRange()
{
	return 20;
}

int DefaultValues::getGustSpeedCalculationTimeRange()
{
	return 30;
}

int DefaultValues::getAutomaticLogSavingIntervalS()
{
	return (10 * 60);
}

bool DefaultValues::getAutomaticLogSavingEnabled()
{
	return false;
}

QString DefaultValues::getAutomaticLogSavingFolderPath()
{
	return "";
}

double DefaultValues::getCompassOffset()
{
	return 0.0;
}
