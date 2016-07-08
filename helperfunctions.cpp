#include "helperfunctions.h"
#include <iostream>

using namespace std;

void printPacket(Packet packet)
{
	cout << "Latitude: " << packet.getLatitude() << endl;
	cout << "Longitude: " << packet.getLongitude() << endl;
	cout << "Rail angle: " << packet.getRailAngle() << endl;
	cout << "Magnetic angle: " << packet.getMagneticNorthAngle() << endl;
	cout << "Wind speed: " << packet.getWindSpeed() << endl;
	cout << "Wind direction: " << (int)packet.getWindDirection() << endl;
	cout << "Pressure: " << packet.getPressure() << endl;
	cout << "Temperature: " << packet.getTemperature() << endl;
	cout << "Battery voltage: " << packet.getBatteryVoltage() << endl;
	cout << "Errors: " << hex << (int)packet.getErrors() << endl;
	cout << "GPS fix age: " << dec << (int)packet.getGPSFixAge() << endl;
	cout << "GPS failed sentences count: " << (int)packet.getGPSFailedSentencesCount() << endl;
	cout << "GPS satellites count: " << (int)packet.getGPSSatellitesCount() << endl;
	cout << "GPS fix detected: " << packet.getGPSFixDetected() << endl;
	cout << "CRC8: " << (int)packet.calculateCRC8() << endl;
	cout << "CRC16: " << (int)packet.calculateCRC16() << endl;
	cout << "CRC32: " << (int)packet.calculateCRC32() << endl;
	if(packet.verifyCRC() == 0) {
		cout << "CRC OK" << endl;
	} else {
		cout << "CRC error: " << (int)packet.verifyCRC() << endl;
	}
}
