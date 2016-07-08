#ifndef LINEARFUNCTION_H
#define LINEARFUNCTION_H


class LinearFunction
{
public:
	LinearFunction();
	void setCoefficients(double A_, double B_);
	double calculateOutput(double x);
private:
	double A, B;
};

#endif // LINEARFUNCTION_H
