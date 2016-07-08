#ifndef BATTERYCHARGECALCULATOR_H
#define BATTERYCHARGECALCULATOR_H
#include <linearfunction.h>

class BatteryChargeCalculator
{
public:
	BatteryChargeCalculator();
	double getCharge(double cellVoltage);
private:
	LinearFunction line1, line2, line3;
};

#endif // BATTERYCHARGECALCULATOR_H
