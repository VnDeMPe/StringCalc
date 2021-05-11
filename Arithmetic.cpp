#include "Arithmetic.h"
#include "CalcException.h"
#include <iostream>
#include <climits>
//Basic Arithmetic operations Class

//To do:
//Expand functionality 
//implement minus power fe 2^-3 

double Arithmetic::Round(double arg1)
{
	try
	{
		double tempValue = (long long int)(arg1 * 100 + .5);
		if (arg1 *100 + .5 > LLONG_MAX)
			throw CalcException("Overflow Exception. Decimal numbers have been rounded. Possible data loss.");
		return (double)tempValue / 100;
	}
	catch (CalcException& error)
	{
		CalcException::LogException(error);
		return round(arg1);
	}
}

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
	try {
		if (arg2 == 0)
		{
			throw CalcZeroException(__FILE__, __LINE__, __func__, arg1, arg2);
		}

		return Arithmetic::Round(arg1 / arg2);
	}

	catch (CalcZeroException& error)
	{
		CalcException::LogException(error);
		return Arithmetic::Round(arg1 / 1);
	}
}

double Arithmetic::Multiply(double arg1, double arg2)
{
	return Arithmetic::Round(arg1 * arg2);
}

double Arithmetic::Power(double arg1, int powerNum)
{
	double result = arg1;
	for (int i = 0; i < (powerNum - 1); i++)
		result = result * arg1;
	return Arithmetic::Round(result);
}

double Arithmetic::Root(double arg1, int rootNum)
{
	return	Arithmetic::Round(pow(arg1, 1.0 / rootNum));
}