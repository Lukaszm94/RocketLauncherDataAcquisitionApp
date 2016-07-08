#include "batterychargecalculator.h"
#include <QDebug>

#define LINE_1_MIN_X 3.0
#define LINE_2_MIN_X 3.67
#define LINE_3_MIN_X 3.8
#define LINE_3_MAX_X 4.15

#define LINE_1_A 25.4
#define LINE_1_B -76.2
#define LINE_2_A 392.3
#define LINE_2_B -1422.74
#define LINE_3_A 91.43
#define LINE_3_B -279.4

BatteryChargeCalculator::BatteryChargeCalculator()
{
	line1.setCoefficients(LINE_1_A, LINE_1_B);
	line2.setCoefficients(LINE_2_A, LINE_2_B);
	line3.setCoefficients(LINE_3_A, LINE_3_B);
}

double BatteryChargeCalculator::getCharge(double cellVoltage)
{
	if(cellVoltage < LINE_1_MIN_X) {
		return line1.calculateOutput(LINE_1_MIN_X);
	} else if(cellVoltage < LINE_2_MIN_X) {
		return line1.calculateOutput(cellVoltage);
	} else if(cellVoltage < LINE_3_MIN_X) {
		return line2.calculateOutput(cellVoltage);
	} else if(cellVoltage < LINE_3_MAX_X) {
		return line3.calculateOutput(cellVoltage);
	} else if(cellVoltage >= LINE_3_MAX_X) {
		return line3.calculateOutput(LINE_3_MAX_X);
	}
	qDebug() << "BatteryChargeCalculator::getCharge(): wrong voltage value: " << cellVoltage;
	return 0;
}


