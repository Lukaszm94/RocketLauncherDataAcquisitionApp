#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>
#include "QtWidgets"

class SettingsWidget : public QWidget
{
	Q_OBJECT
public:
	explicit SettingsWidget(QWidget *parent = 0);
	int getAverageSpeedCalculationTimeRange();
	int getGustSpeedCalculationTimeRange();
	bool getAutomaticLogSavingEnabled();
	int getAutomaticLogSavingIntervalS();
	QString getAutomaticLogSavingFolderPath();
	double getCompassOffset();
signals:
	void settingsChanged();
private slots:
	void onApplyButtonClicked();
	void onBrowseAutomaticLogSavingFolderPathClicked();
private:
	QLineEdit* averageSpeedCalculationTimeRangeLineEdit;
	QLineEdit* gustSpeedCalculationTimeRangeLineEdit;
	QCheckBox* enableAutomaticLogSavingCheckbox;
	QLineEdit* automaticLogSavingIntervalSLineEdit;
	QLineEdit* automaticLogSavingFolderPathLineEdit;
	QPushButton* automaticLogSavingFolderPathButton;
	QLineEdit* compassOffsetLineEdit;
	QPushButton* applyButton;
};

#endif // SETTINGSWIDGET_H
