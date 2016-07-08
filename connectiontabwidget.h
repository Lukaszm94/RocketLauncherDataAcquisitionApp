#ifndef CONNECTIONTABWIDGET_H
#define CONNECTIONTABWIDGET_H
#include <QString>
#include <QtWidgets>


class ConnectionTabWidget : public QWidget
{
	Q_OBJECT
public:
	ConnectionTabWidget(QWidget* parent = 0);
	void setSerialConnected(bool connected = true);
signals:
	void connectButtonClicked(QString serialPortName);
private slots:
	void refreshSerialPorts();
	void onConnectButtonClicked();
private:
	QComboBox* serialPortComboBox;
	QPushButton* refreshButton;
	QPushButton* connectButton;
	QVBoxLayout* mainLayout;
};

#endif // CONNECTIONTABWIDGET_H
