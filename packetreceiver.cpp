#include "packetreceiver.h"
#include <QDebug>
#include <iostream>
#include <QTime>
#include "helperfunctions.h"
#include "hexdump.h"

#define PACKET_SIZE (sizeof(PacketStruct))

using namespace std;

PacketReceiver::PacketReceiver(QObject *parent) : QObject(parent)
{
	lastValidPacketTimestamp = 0;
	resetPacketCounters();
}

Packet PacketReceiver::getPacket()
{
	return packet;
}

int PacketReceiver::getValidPacketCount()
{
	return validPacketCounter;
}

int PacketReceiver::getInvalidPacketCount()
{
	return invalidPacketCounter;
}

void PacketReceiver::resetPacketCounters()
{
	validPacketCounter = invalidPacketCounter = 0;
}

int PacketReceiver::getLastValidPacketTimestamp()
{
	return lastValidPacketTimestamp;
}

void PacketReceiver::onNewDataReceived(QByteArray data)
{
	buffer.append(data);
	if(buffer.size() > (int)PACKET_SIZE) {
		qDebug() << "PacketReceiver: received too much data, clearing buffer";
		buffer.clear();
		return;
	}
	if(buffer.size() == PACKET_SIZE) {
		unpackBufferData();
		if(packet.verifyCRC() == 0) {
			//qDebug() << "PacketReceiver: received valid packet";
			validPacketCounter++;
			lastValidPacketTimestamp = QTime::currentTime().msecsSinceStartOfDay();
			emit validPacketReceived();
		} else {
			qDebug() << "PacketReceiver: received invalid packet!";
			invalidPacketCounter++;
			emit invalidPacketReceived();
		}
	}
}

void PacketReceiver::unpackBufferData()
{
	char* bufferData = buffer.data();
	char bufferCopy[PACKET_SIZE];
	memcpy(bufferCopy, bufferData, PACKET_SIZE);
	memcpy(bufferData + 12, bufferCopy + 10, 16);
	bufferData[10] = bufferData[11] = 0;
	buffer.clear();
	packet.loadPacketData(bufferData);
}

