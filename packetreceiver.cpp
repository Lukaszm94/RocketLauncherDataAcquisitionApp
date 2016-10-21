#include "packetreceiver.h"
#include <QDebug>
#include <iostream>
#include <QTime>
#include "helperfunctions.h"
#include "hexdump.h"

#define BINARY_PACKET_SIZE 26

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
	qDebug() << "PacketReceiver::onNewDataReceived(): appending " << data.size() << " bytes";
	if(buffer.size() > (int)BINARY_PACKET_SIZE) {
		qDebug() << "PacketReceiver: received too much data, clearing buffer";
		buffer.clear();
		return;
	}
	if(buffer.size() == BINARY_PACKET_SIZE) {
		unpackBufferData();
		if(packet.verifyCRC() == 0) {
			qDebug() << "PacketReceiver: received valid packet";
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
	uint8_t* bufferData = (uint8_t*)buffer.data();
	PacketStruct packetStruct;
	packetStruct.windSpeed = bufferData[0];
	packetStruct.windDirection = bufferData[1];
	packetStruct.batteryVoltage = bufferData[2];
	packetStruct.errors = bufferData[3];
	packetStruct.gpsFixAge = bufferData[4];
	packetStruct.gpsFailedSentencesCount = bufferData[5];
	packetStruct.gpsStatus = bufferData[6];
	packetStruct.crc8 = bufferData[7];
	packetStruct.crc16 = bufferData[8];
	packetStruct.crc32 = bufferData[9];
	packetStruct.railAngle = ((uint16_t)bufferData[10] << 8) | bufferData[11];
	packetStruct.magneticNorthAngle = ((uint16_t)bufferData[12] << 8) | bufferData[13];
	packetStruct.pressure = ((uint16_t)bufferData[14] << 8) | bufferData[15];
	packetStruct.temperature = ((uint16_t)bufferData[16] << 8) | bufferData[17];
	packetStruct.latitude = ((int32_t)bufferData[18] << 24) | ((int32_t)bufferData[19] << 16) | ((int32_t)bufferData[20] << 8) | ((int32_t)bufferData[21]);
	packetStruct.longitude = ((int32_t)bufferData[22] << 24) | ((int32_t)bufferData[23] << 16) | ((int32_t)bufferData[24] << 8) | ((int32_t)bufferData[25]);

	packet = Packet(packetStruct);
	buffer.clear();
}

