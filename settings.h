#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>

struct Settings
{
	int averageSpeedCalculationTimeRange;
	int gustSpeedCalculationTimeRange;

	bool automaticLogSavingEnabled;
	int automaticLogSavingIntervalS;
	QString automaticLogSavingFolderPath;

	double compassOffset;
};

#endif // SETTINGS_H
