#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include "settings.h"
#include "settingswidget.h"

class SettingsManager
{
public:
	SettingsManager();
	Settings getSettings();
	bool loadSavedSettings();
	bool updateSettings(SettingsWidget* widget);
	bool saveSettings();

private:
	QSettings* qsettings;
	Settings settings;
};

#endif // SETTINGSMANAGER_H
