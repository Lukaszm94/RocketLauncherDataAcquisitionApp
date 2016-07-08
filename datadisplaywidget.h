#ifndef DATADISPLAYWIDGET_H
#define DATADISPLAYWIDGET_H
#include <QtWidgets>
#include <qwt/qwt_compass.h>
#include "timeplotwidget.h"
#include "guipacket.h"

class DataDisplayWidget : public QWidget
{
	Q_OBJECT
public:
	DataDisplayWidget(QWidget* parent = 0);
	void updateData(GUIPacket packet);

private:
	void setWindDirection(QString str, QColor color = Qt::black);
	void setWindSpeed(QString str, QColor color = Qt::black);
	void setAirTemperature(QString str, QColor color = Qt::black);
	void setAirPressure(QString str, QColor color = Qt::black);
	void setRailAngle(QString str, QColor color = Qt::black);
	void setOrientation(QString str, QColor color = Qt::black);
	void setLatitude(QString str, QColor color = Qt::black);
	void setLongitude(QString str, QColor color = Qt::black);
	void setBatteryVoltageLabel(QString str, QColor color = Qt::black);
	void setColorOnLabel(QLabel* label, QColor color);

	QLabel* windDirectionLabel;
	QLabel* windSpeedLabel;
	QLabel* airTemperatureLabel;
	QLabel* airPressureLabel;
	QLabel* railAngleLabel;
	QLabel* orientationLabel;
	QLabel* latitudeLabel;
	QLabel* longitudeLabel;
	QLabel* batteryVoltageLabel;
	QwtCompass* railOrientationCompass;

	QVBoxLayout* mainLayout;
	QVBoxLayout* windDataLayout;
	QVBoxLayout* airDataLayout;
	QVBoxLayout* launcherDataLayout;
	QHBoxLayout* topDataLayout;
	TimePlotWidget* windPlot;
	int timestamp;
	int y1, y2;
};

#endif // DATADISPLAYWIDGET_H
