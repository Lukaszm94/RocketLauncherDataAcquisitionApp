#include "datadisplaywidget.h"
#include <qwt/qwt_dial_needle.h>



DataDisplayWidget::DataDisplayWidget(QWidget *parent) : QWidget(parent)
{
	windDirectionLabel = new QLabel;
	windSpeedLabel = new QLabel;
	airTemperatureLabel = new QLabel;
	airPressureLabel = new QLabel;
	railAngleLabel = new QLabel;
	orientationLabel = new QLabel;
	latitudeLabel = new QLabel;
	longitudeLabel = new QLabel;
	batteryVoltageLabel = new QLabel;
	railOrientationCompass = new QwtCompass;
	mainLayout = new QVBoxLayout;
	windDataLayout = new QVBoxLayout;
	airDataLayout = new QVBoxLayout;
	launcherDataLayout = new QVBoxLayout;
	topDataLayout = new QHBoxLayout;
	windPlot = new TimePlotWidget;


	railOrientationCompass->setNeedle( new QwtDialSimpleNeedle( QwtDialSimpleNeedle::Ray, false, Qt::yellow ) );
	railOrientationCompass->setMinimumSize(150, 150);

	QFont font("Arial", 14);
	windDirectionLabel->setFont(font);
	windSpeedLabel->setFont(font);

	QLabel* windDataLabel = new QLabel("<b>Wind data</b>");
	QLabel* airDataLabel = new QLabel("<b>Atmospheric data</b>");
	QLabel* launcherDataLabel = new QLabel("<b>Launcher data</b>");

	windDataLabel->setFont(font);
	windDirectionLabel->setFont(font);
	windSpeedLabel->setFont(font);
	airDataLabel->setFont(font);
	airTemperatureLabel->setFont(font);
	airPressureLabel->setFont(font);
	launcherDataLabel->setFont(font);
	railAngleLabel->setFont(font);
	orientationLabel->setFont(font);
	latitudeLabel->setFont(font);
	longitudeLabel->setFont(font);

	windDataLayout->addWidget(windDataLabel);
	windDataLayout->addWidget(windDirectionLabel);
	windDataLayout->addWidget(windSpeedLabel);
	airDataLayout->addWidget(airDataLabel);
	airDataLayout->addWidget(airTemperatureLabel);
	airDataLayout->addWidget(airPressureLabel);


	launcherDataLayout->addWidget(launcherDataLabel);
	launcherDataLayout->addWidget(railAngleLabel);
	launcherDataLayout->addWidget(orientationLabel);
	launcherDataLayout->addWidget(latitudeLabel);
	launcherDataLayout->addWidget(longitudeLabel);
	launcherDataLayout->addWidget(batteryVoltageLabel);

	topDataLayout->addLayout(windDataLayout);
	topDataLayout->addLayout(airDataLayout);
	topDataLayout->addLayout(launcherDataLayout);
	//topDataLayout->addWidget(railOrientationCompass);;

	mainLayout->addLayout(topDataLayout);
	mainLayout->addWidget(windPlot);
	this->setLayout(mainLayout);

	windPlot->addGraph("Average", "red");
	windPlot->addGraph("Gust", "blue");
	windPlot->addGraph("Current", "green");
	windPlot->setYAxisLabel("Wind [m/s]");
}

void DataDisplayWidget::setWindDirection(QString str, QColor color)
{
	QString text = "Direction: " + str;
	windDirectionLabel->setText(text);
	setColorOnLabel(windDirectionLabel, color);
}

void DataDisplayWidget::setWindSpeed(QString str, QColor color)
{
	QString text = "Speed: " + str;
	windSpeedLabel->setText(text);
	setColorOnLabel(windSpeedLabel, color);
}

void DataDisplayWidget::setAirTemperature(QString str, QColor color)
{
	QString text = "Temperature: " + str;
	airTemperatureLabel->setText(text);
	setColorOnLabel(airTemperatureLabel, color);
}

void DataDisplayWidget::setAirPressure(QString str, QColor color)
{
	QString text = "Pressure: " + str;
	airPressureLabel->setText(text);
	setColorOnLabel(airPressureLabel, color);
}

void DataDisplayWidget::setRailAngle(QString str, QColor color)
{
	QString text = "Rail angle: " + str;
	railAngleLabel->setText(text);
	setColorOnLabel(railAngleLabel, color);
}

void DataDisplayWidget::setOrientation(QString str, QColor color)
{
	QString text = "Orientation: " + str;
	orientationLabel->setText(text);
	setColorOnLabel(orientationLabel, color);
}

void DataDisplayWidget::setLatitude(QString str, QColor color)
{
	QString text = "Latitude: " + str;
	latitudeLabel->setText(text);
	setColorOnLabel(latitudeLabel, color);
}

void DataDisplayWidget::setLongitude(QString str, QColor color)
{
	QString text = "Longitude: " + str;
	longitudeLabel->setText(text);
	setColorOnLabel(longitudeLabel, color);
}

void DataDisplayWidget::setBatteryVoltageLabel(QString str, QColor color)
{
	QString text = "Battery: " + str;
	batteryVoltageLabel->setText(text);
	setColorOnLabel(batteryVoltageLabel, color);
}

void DataDisplayWidget::setColorOnLabel(QLabel *label, QColor color)
{
	QPalette palette = label->palette();
	palette.setColor(label->foregroundRole(), color);
	label->setPalette(palette);
}

void DataDisplayWidget::updateData(GUIPacket packet)
{
	QColor okColor = Qt::black;
	QColor errorColor = Qt::red;
	QColor currentColor = okColor;

	if(packet.isWindVaneErrorFlagSet()) {
		currentColor = errorColor;
	} else {
		currentColor = okColor;
	}
	setWindDirection(packet.getWindDirection(), currentColor);

	/*if(packet.isAnemometerErrorFlagSet()) {
		currentColor = errorColor;
	} else {
		currentColor = okColor;
	}*/
	setWindSpeed(packet.getActualWindSpeedStr(), currentColor);

	if(packet.isBarometerErrorFlagSet()) {
		currentColor = errorColor;
	} else {
		currentColor = okColor;
	}
	setAirTemperature(packet.getTemperature(), currentColor);
	setAirPressure(packet.getPressure(), currentColor);

	if(packet.isAccelerometerErrorFlagSet()) {
		currentColor = errorColor;
	} else {
		currentColor = okColor;
	}
	setRailAngle(packet.getRailAngle(), currentColor);

	if(packet.isMagnetometerErrorFlagSet()) {
		currentColor = errorColor;
	} else {
		currentColor = okColor;
	}
	setOrientation(packet.getNorthAngle(), currentColor);

	if(!packet.isGPSFixDetected()) {
		currentColor = errorColor;
	} else {
		currentColor = okColor;
	}
	setLatitude(packet.getLatitude(), currentColor);
	setLongitude(packet.getLongitude(), currentColor);

	if(packet.getBatteryVoltage() <= 7.1) {
		currentColor = errorColor;
	} else {
		currentColor = okColor;
	}
	setBatteryVoltageLabel(packet.getBatteryStateStr(), currentColor);

	windPlot->onNewData(packet.getAverageWindSpeed(), packet.getGustSpeed(), packet.getCurrentWindSpeed());

}
