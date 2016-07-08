#ifndef PACKETRECEIVER_H
#define PACKETRECEIVER_H

#include <QObject>
#include <QByteArray>
#include "packet.h"

class PacketReceiver : public QObject
{
	Q_OBJECT
public:
	PacketReceiver(QObject* parent = 0);
	Packet getPacket();
	int getValidPacketCount();
	int getInvalidPacketCount();
	void resetPacketCounters();
	int getLastValidPacketTimestamp();
public slots:
	void onNewDataReceived(QByteArray data);
signals:
	void validPacketReceived();
	void invalidPacketReceived();
private:
	void unpackBufferData();

	QByteArray buffer;
	Packet packet;
	int validPacketCounter, invalidPacketCounter;
	int lastValidPacketTimestamp;
};

#endif // PACKETRECEIVER_H
