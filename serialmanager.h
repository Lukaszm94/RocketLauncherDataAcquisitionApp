#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H
#include <iostream>
#include <QObject>
#include <QSerialPort>
#include <QDebug>
#include "packet.h"

using namespace std;

#define BUFFER_SIZE 28
#define PACKET_SIZE 28

class SerialManager : public QObject
{
	Q_OBJECT
public:
	SerialManager(QObject* parent = 0);
	bool isConnected();
	bool connectToSerialPort(QString portName);
	bool disconnectFromSerialPort();

private slots:
	void onReadyRead();
	void onSerialPortError(QSerialPort::SerialPortError error);
signals:
	void onNewDataReady(QByteArray data);
	void serialPortError(QString errorMessage);
private:


	QSerialPort* serialPort;
	Packet packet;
};

#endif // SERIALMANAGER_H
