#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	tabWidget = new QTabWidget;
	connectionTabWidget = new ConnectionTabWidget;
	dataDisplayWidget = new DataDisplayWidget;
	dataLoggingWidget = new DataLoggingWidget;
	statusWidget = new StatusWidget;
	skaLogoLabel = new QLabel;
	sectionLogoLabel = new QLabel;
	centralWidget = new QWidget;
	settingsWidget = new SettingsWidget;
	topLayout = new QHBoxLayout;
	mainLayout = new QVBoxLayout;
	QPixmap* skaLogoPixmap = new QPixmap(":/img/img/logo.png");
	QPixmap* sectionLogoPixmap = new QPixmap(":/img/img/logo_sr.png");

	tabWidget->addTab(connectionTabWidget, "Connection");
	tabWidget->addTab(dataDisplayWidget, "Data");
	tabWidget->addTab(dataLoggingWidget, "Log");
	tabWidget->addTab(settingsWidget, "Settings");

	skaLogoLabel->setPixmap(*skaLogoPixmap);
	sectionLogoLabel->setPixmap(*sectionLogoPixmap);
	topLayout->addWidget(statusWidget);
	topLayout->addWidget(skaLogoLabel);
	topLayout->addWidget(sectionLogoLabel);

	mainLayout->addLayout(topLayout);
	mainLayout->addWidget(tabWidget);
	centralWidget->setLayout(mainLayout);
	this->setCentralWidget(centralWidget);
	this->setWindowTitle("Rocket launcher data acquisition");
	connect(connectionTabWidget, SIGNAL(connectButtonClicked(QString)), this, SLOT(onConnectSerialButtonClicked(QString)));
	connect(dataLoggingWidget, SIGNAL(startButtonClicked()), this, SLOT(onStartLoggingButtonClicked()));
	connect(dataLoggingWidget, SIGNAL(clearLogButtonClicked()), this, SLOT(onClearLogButtonClicked()));
	connect(dataLoggingWidget, SIGNAL(saveButtonClicked()), this, SLOT(onSaveDataLogButtonClicked()));
	connect(settingsWidget, SIGNAL(settingsChanged()), this, SLOT(onSettingsChanged()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::updateGUI(GUIPacket guiPacket)
{
	dataDisplayWidget->updateData(guiPacket);

}

void MainWindow::appendDataLog(QString str)
{
	dataLoggingWidget->appendLog(str);
}

void MainWindow::clearDataLog()
{
	dataLoggingWidget->clearLog();
}

void MainWindow::setSerialConnected(bool connected)
{
	statusWidget->setConnected(connected);
	connectionTabWidget->setSerialConnected(connected);
	if(connected) {
		tabWidget->setCurrentIndex(1);
	}
}

void MainWindow::setReceivingDataIcon(bool receiving)
{
	statusWidget->setReceivingData(receiving);
}

void MainWindow::setLogging(bool loggingEnabled)
{
	statusWidget->setLogging(loggingEnabled);
	dataLoggingWidget->setLogging(loggingEnabled);
}

int MainWindow::getAverageSpeedCalculationTimeRange()
{
	return settingsWidget->getAverageSpeedCalculationTimeRange();
}

int MainWindow::getGustSpeedCalculationTimeRange()
{
	return settingsWidget->getGustSpeedCalculationTimeRange();
}

bool MainWindow::getAutomaticLogSavingEnabled()
{
	return settingsWidget->getAutomaticLogSavingEnabled();
}

int MainWindow::getAutomaticLogSavingIntervalS()
{
	return settingsWidget->getAutomaticLogSavingIntervalS();
}

QString MainWindow::getAutomaticLogSavingFolderPath()
{
	return settingsWidget->getAutomaticLogSavingFolderPath();
}

QString MainWindow::getSaveLogFilePath()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Log"), "", tr("CSV data (*.csv)"));
	return fileName;
}

double MainWindow::getCompassOffset()
{
	return settingsWidget->getCompassOffset();
}

void MainWindow::onConnectSerialButtonClicked(QString portName)
{
	emit connectSerialButtonClicked(portName);
}

void MainWindow::onSaveDataLogButtonClicked()
{
	emit saveDataLogButtonClicked();
}

void MainWindow::onStartLoggingButtonClicked()
{
	emit startLoggingButtonClicked();
}

void MainWindow::onClearLogButtonClicked()
{
	emit clearLogButtonClicked();
}

void MainWindow::onSettingsChanged()
{
	emit settingsChanged();
}

SettingsWidget *MainWindow::getSettingsWidget()
{
	return settingsWidget;
}
