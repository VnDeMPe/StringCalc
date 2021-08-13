#include "Arithmetic.h"
#include "CalcException.h"
#include <iostream>
#include <climits>
//Basic Arithmetic operations Class

//To do:
//Expand functionality 
//implement minus power for example  2^-3  - done

//double Arithmetic::Round(double arg1)		// old version
//{
//	try
//	{
//		double tempValue = (long long int)(arg1 * 10000000 + .5);
//		if (arg1 *10000000 + .5 > LLONG_MAX)
//			throw CalcException("Overflow Exception. Decimal numbers have been rounded. Possible data loss.");
//		return (double)tempValue / 10000000;
//	}
//	catch (CalcException& error)
//	{
//		CalcException::LogException(error);
//		return round(arg1);
//	}
//}

double Arithmetic::Round(double arg1)
{
	double tempValue = abs(arg1) - abs((long long int)arg1); 
	if (tempValue < 0.00001 || tempValue > 0.999999)
		return round(arg1);
	else
		return arg1;
}

double Arithmetic::Round(double arg1, bool endRound, int numDecimals)
{
	if (endRound)
	{
		try
		{
			long int decimalsMultplier = Power(10, numDecimals);
			double tempValue = (long long int)(arg1 * decimalsMultplier);
			if (arg1 * decimalsMultplier > LLONG_MAX)
				throw CalcException("Overflow Exception. Decimal numbers have been rounded. Possible data loss.");
			return (double)tempValue / decimalsMultplier;
		}
		catch (CalcException& error)
		{
			CalcException::LogException(error);
			return round(arg1);
		}
	}
	else
		Round(arg1);
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
	if (powerNum > 0)
	{
		for (int i = 0; i < (powerNum - 1); i++)
			result = result * arg1;
	}
	else
	{
		result = Power((1 / arg1), abs(powerNum));
	}

	return Arithmetic::Round(result);
}

double Arithmetic::Root(double arg1, int rootNum)
{
	return	Arithmetic::Round(pow(arg1, 1.0 / rootNum));
}