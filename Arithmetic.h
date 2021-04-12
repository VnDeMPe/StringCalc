#pragma once
#ifndef ARITHMETIC_H_
#define ARITHMETIC_H_



#include <math.h>
#include <iostream>

class Arithmetic
{
public:
	static double Add(double arg1, double arg2);
	static double Substract(double arg1, double arg2);
	static double Multiply(double aarg1, double arg2);
	static double Divide(double arg1, double arg2);
	static double Power(double arg1, int powerNum);
	static double Root(double arg1, int rootNum);
};

#endif // !ARITHMETIC_H_