#include "settingsmanager.h"
#include "defaultvalues.h"

SettingsManager::SettingsManager()
{
	qsettings = new QSettings("SR_SKA", "RocketLauncherDataAcquisitionApp");

	settings.automaticLogSavingEnabled = DefaultValues::getAutomaticLogSavingEnabled();
	settings.automaticLogSavingFolderPath = DefaultValues::getAutomaticLogSavingFolderPath();
	settings.automaticLogSavingIntervalS = DefaultValues::getAutomaticLogSavingIntervalS();

	settings.averageSpeedCalculationTimeRange = DefaultValues::getAverageSpeedCalculationTimeRange();
	settings.gustSpeedCalculationTimeRange = DefaultValues::getGustSpeedCalculationTimeRange();

	settings.compassOffset = DefaultValues::getCompassOffset();
}

Settings SettingsManager::getSettings()
{
	return settings;
}

bool SettingsManager::loadSavedSettings()
{
	settings.automaticLogSavingEnabled = qsettings->value("automaticLogSavingEnabled", settings.automaticLogSavingEnabled).toBool();
	settings.automaticLogSavingFolderPath = qsettings->value("automaticLogSavingFolderPath", settings.automaticLogSavingFolderPath).toString();
	settings.automaticLogSavingIntervalS = qsettings->value("automaticLogSavingIntervalS", settings.automaticLogSavingIntervalS).toInt();

	settings.averageSpeedCalculationTimeRange = qsettings->value("averageSpeedCalculationTimeRange", settings.averageSpeedCalculationTimeRange).toInt();
	settings.gustSpeedCalculationTimeRange = qsettings->value("gustSpeedCalculationTimeRange", settings.gustSpeedCalculationTimeRange).toInt();

	settings.compassOffset = qsettings->value("compassOffset", settings.compassOffset).toDouble();
}

bool SettingsManager::updateSettings(SettingsWidget *widget)
{
	Settings newSettings;
	newSettings.automaticLogSavingEnabled = widget->getAutomaticLogSavingEnabled();
	newSettings.automaticLogSavingFolderPath = widget->getAutomaticLogSavingFolderPath();
	newSettings.automaticLogSavingIntervalS = widget->getAutomaticLogSavingIntervalS();

	newSettings.averageSpeedCalculationTimeRange = widget->getAverageSpeedCalculationTimeRange();
	newSettings.gustSpeedCalculationTimeRange = widget->getGustSpeedCalculationTimeRange();

	newSettings.compassOffset = widget->getCompassOffset();

	settings = newSettings;
}

bool SettingsManager::saveSettings()
{
	qsettings->setValue("automaticLogSavingEnabled", settings.automaticLogSavingEnabled);
	qsettings->setValue("automaticLogSavingFolderPath", settings.automaticLogSavingFolderPath);
	qsettings->setValue("automaticLogSavingIntervalS", settings.automaticLogSavingIntervalS);

	qsettings->setValue("averageSpeedCalculationTimeRange", settings.averageSpeedCalculationTimeRange);
	qsettings->setValue("gustSpeedCalculationTimeRange", settings.gustSpeedCalculationTimeRange);

	qsettings->setValue("compassOffset", settings.compassOffset);

}
