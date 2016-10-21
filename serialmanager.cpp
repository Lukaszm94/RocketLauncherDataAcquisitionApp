#include "serialmanager.h"

SerialManager::SerialManager(QObject *parent) : QObject(parent)
{
	serialPort = new QSerialPort;
	connect(serialPort, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
	connect(serialPort, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(onSerialPortError(QSerialPort::SerialPortError)));
}

bool SerialManager::isConnected()
{
	return serialPort->isOpen();
}

bool SerialManager::connectToSerialPort(QString portName)
{
	if(serialPort->isOpen()) {
		qDebug() << "SerialManager::connectToSerialPort: serialPort was open, closing";
		serialPort->close();
	}
	serialPort->setPortName(portName);
	if(!serialPort->open(QSerialPort::ReadOnly)) {
		qDebug() << "SerialManager::connectToSerialPort: unable to open serial port " << portName;
		return false;
	}
	serialPort->setFlowControl(QSerialPort::NoFlowControl);
	serialPort->setBaudRate(QSerialPort::Baud115200);
	if(!serialPort->clear()) {
		qDebug() << "SerialManager::connectToSerialPort: clearing buffer failed";
	}
	return true;
}

bool SerialManager::disconnectFromSerialPort()
{
	if(!serialPort->isOpen()) {
		qDebug() << "SerialManager::disconnectFromSerialPort: serialPort was closed";
		return false;
	}
	serialPort->close();
	return true;
}

void SerialManager::onReadyRead()
{
	if(serialPort->bytesAvailable() == 0) {
		qDebug() << "SerialManager::onReadyRead: no bytes available";
		return;
	}
	emit onNewDataReady(serialPort->readAll());
}

void SerialManager::onSerialPortError(QSerialPort::SerialPortError error)
{
	if(error == QSerialPort::NoError) {
		return;
	}
	QString str = QString::number((int)error);
	emit serialPortError(str);
}
