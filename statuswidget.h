#ifndef STATUSWIDGET_H
#define STATUSWIDGET_H
#include <QtWidgets>

class StatusWidget : public QWidget
{
	Q_OBJECT
public:
	StatusWidget(QWidget* parent = 0);
	void setConnected(bool on);
	void setReceivingData(bool on);
	void setLogging(bool on);
private:
	QPixmap* greenIcon;
	QPixmap* grayIcon;
	QPixmap* redIcon;
	QLabel* connectedIconLabel;
	QLabel* receivingDataIconLabel;
	QLabel* loggingIconLabel;
};

#endif // STATUSWIDGET_H
