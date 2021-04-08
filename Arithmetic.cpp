#include "Arithmetic.h"

//Basic Arithmetic operations Class

//To do:
//Add Try Catch Throw !!!! 
//Expand functionality 

double Arithmetic::Add(double arg1, double arg2)
{
	return arg1 + arg2;
}

double Arithmetic::Substract(double arg1, double arg2)
{
	return arg1 - arg2;
}

double Arithmetic::Divide(double arg1, double arg2)
{
	return arg1 / arg2;
}

double Arithmetic::Multiply(double arg1, double arg2)
{
	return arg1 * arg2;
}

double Arithmetic::Power(double arg1, int powerNum)
{
	double result = arg1;
	for (int i = 0; i < (powerNum - 1); i++)
		result = result * arg1;
	return result;
}

double Arithmetic::Root(double arg1, int rootNum)
{
	return	pow(arg1, 1.0 / rootNum);
}