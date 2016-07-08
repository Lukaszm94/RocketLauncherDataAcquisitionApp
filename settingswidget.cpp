#include "settingswidget.h"
#include <QDebug>
#include "defaultvalues.h"

SettingsWidget::SettingsWidget(QWidget *parent) : QWidget(parent)
{
	averageSpeedCalculationTimeRangeLineEdit = new QLineEdit;
	gustSpeedCalculationTimeRangeLineEdit = new QLineEdit;
	applyButton = new QPushButton("APPLY");
	enableAutomaticLogSavingCheckbox = new QCheckBox;
	automaticLogSavingIntervalSLineEdit = new QLineEdit;
	automaticLogSavingFolderPathLineEdit = new QLineEdit;
	compassOffsetLineEdit = new QLineEdit;
	automaticLogSavingFolderPathButton = new QPushButton("Browse");

	QHBoxLayout* avgSpeedLayout = new QHBoxLayout;
	avgSpeedLayout->addWidget(new QLabel("Average"));
	avgSpeedLayout->addStretch();
	avgSpeedLayout->addWidget(averageSpeedCalculationTimeRangeLineEdit);
	avgSpeedLayout->addWidget(new QLabel("s"));

	QHBoxLayout* gustSpeedLayout = new QHBoxLayout;
	gustSpeedLayout->addWidget(new QLabel("Gusts"));
	gustSpeedLayout->addStretch();
	gustSpeedLayout->addWidget(gustSpeedCalculationTimeRangeLineEdit);
	gustSpeedLayout->addWidget(new QLabel("s"));

	QHBoxLayout* enableAutomaticLogSavingLayout = new QHBoxLayout;
	enableAutomaticLogSavingLayout->addWidget(new QLabel("Enable"));
	enableAutomaticLogSavingLayout->addStretch();
	enableAutomaticLogSavingLayout->addWidget(enableAutomaticLogSavingCheckbox);

	QHBoxLayout* automaticLogSavingIntervalLayout = new QHBoxLayout;
	automaticLogSavingIntervalLayout->addWidget(new QLabel("Interval"));
	automaticLogSavingIntervalLayout->addStretch();
	automaticLogSavingIntervalLayout->addWidget(automaticLogSavingIntervalSLineEdit);
	automaticLogSavingIntervalLayout->addWidget(new QLabel("s"));

	QHBoxLayout* automaticLogSavingFolderPathLayout = new QHBoxLayout;
	automaticLogSavingFolderPathLayout->addWidget(new QLabel("Folder path"));
	automaticLogSavingFolderPathLayout->addStretch();
	automaticLogSavingFolderPathLayout->addWidget(automaticLogSavingFolderPathLineEdit);
	automaticLogSavingFolderPathLayout->addWidget(automaticLogSavingFolderPathButton);

	QHBoxLayout* compassOffsetLayout = new QHBoxLayout;
	compassOffsetLayout->addWidget(new QLabel("Compass offset"));
	compassOffsetLayout->addStretch();
	compassOffsetLayout->addWidget(compassOffsetLineEdit);
	compassOffsetLayout->addWidget(new QLabel("deg"));

	QHBoxLayout* buttonsLayout = new QHBoxLayout;
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(applyButton);

	QVBoxLayout* mainColumnLayout = new QVBoxLayout;
	mainColumnLayout->addWidget(new QLabel("<b>Wind speed calculation range</b>"));
	mainColumnLayout->addLayout(avgSpeedLayout);
	mainColumnLayout->addLayout(gustSpeedLayout);
	mainColumnLayout->addWidget(new QLabel("<b>Automatic log saving</b>"));
	mainColumnLayout->addLayout(enableAutomaticLogSavingLayout);
	mainColumnLayout->addLayout(automaticLogSavingIntervalLayout);
	mainColumnLayout->addLayout(automaticLogSavingFolderPathLayout);
	mainColumnLayout->addWidget(new QLabel("<b>Compass</b>"));
	mainColumnLayout->addLayout(compassOffsetLayout);
	mainColumnLayout->addStretch();
	mainColumnLayout->addLayout(buttonsLayout);

	QHBoxLayout* mainLayout = new QHBoxLayout;
	mainLayout->addLayout(mainColumnLayout);
	mainLayout->addStretch();

	this->setLayout(mainLayout);
	connect(applyButton, SIGNAL(clicked(bool)), this, SLOT(onApplyButtonClicked()));
	connect(enableAutomaticLogSavingCheckbox, SIGNAL(toggled(bool)), automaticLogSavingIntervalSLineEdit, SLOT(setEnabled(bool)));
	connect(automaticLogSavingFolderPathButton, SIGNAL(clicked()), this, SLOT(onBrowseAutomaticLogSavingFolderPathClicked()));
	averageSpeedCalculationTimeRangeLineEdit->setText(QString::number(DefaultValues::getAverageSpeedCalculationTimeRange()));
	gustSpeedCalculationTimeRangeLineEdit->setText(QString::number(DefaultValues::getGustSpeedCalculationTimeRange()));
	automaticLogSavingIntervalSLineEdit->setText(QString::number(DefaultValues::getAutomaticLogSavingIntervalS()));
	enableAutomaticLogSavingCheckbox->setChecked(DefaultValues::getAutomaticLogSavingEnabled());
	automaticLogSavingIntervalSLineEdit->setEnabled(DefaultValues::getAutomaticLogSavingEnabled());
	compassOffsetLineEdit->setText(QString::number(DefaultValues::getCompassOffset()));
	averageSpeedCalculationTimeRangeLineEdit->setFixedWidth(60);
	gustSpeedCalculationTimeRangeLineEdit->setFixedWidth(60);
	automaticLogSavingIntervalSLineEdit->setFixedWidth(60);
	compassOffsetLineEdit->setFixedWidth(60);
}

int SettingsWidget::getAverageSpeedCalculationTimeRange()
{
	int time = averageSpeedCalculationTimeRangeLineEdit->text().toInt();
	qDebug() << "SettingsWidget::getAverageSpeedCalculationTimeRange(): time= " << time;
	return time;
}

int SettingsWidget::getGustSpeedCalculationTimeRange()
{
	int time = gustSpeedCalculationTimeRangeLineEdit->text().toInt();
	qDebug() << "SettingsWidget::getGustSpeedCalculationTimeRange(): time= " << time;
	return time;
}

bool SettingsWidget::getAutomaticLogSavingEnabled()
{
	return enableAutomaticLogSavingCheckbox->isChecked();
}

int SettingsWidget::getAutomaticLogSavingIntervalS()
{
	int time = automaticLogSavingIntervalSLineEdit->text().toInt();
	qDebug() << "SettingsWidget::getAutomaticLogSavingIntervalS(): time= " << time;
	return time;
}

QString SettingsWidget::getAutomaticLogSavingFolderPath()
{
	return automaticLogSavingFolderPathLineEdit->text();
}

double SettingsWidget::getCompassOffset()
{
	return compassOffsetLineEdit->text().toDouble();
}

void SettingsWidget::onApplyButtonClicked()
{
	emit settingsChanged();
}

void SettingsWidget::onBrowseAutomaticLogSavingFolderPathClicked()
{
	QString folderPath = QFileDialog::getExistingDirectory();
	automaticLogSavingFolderPathLineEdit->setText(folderPath);
}
