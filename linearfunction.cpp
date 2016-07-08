#include "linearfunction.h"

LinearFunction::LinearFunction()
{
	A = B = 0;
}

void LinearFunction::setCoefficients(double A_, double B_)
{
	A = A_;
	B = B_;
}

double LinearFunction::calculateOutput(double x)
{
	return (A * x + B);
}
