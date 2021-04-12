#pragma once
#ifndef ARITHPROC_H_
#define ARITHPROC_H_


#include "Arithmetic.h"
#include <vector>
#include <string>

//getters setters


class ArithProc : public Arithmetic
{
protected: 
	  //inline static std::list<double> stringValues;
	  //inline static std::list<char> stringOperands;
	  inline static std::vector<double> arrayOfValues;
	  inline static std::vector<char> arrayOfOperators;
	  inline static std::vector<int> OperatorPositionLvl1, OperatorPositionLvl2, OperatorPositionLvl3;
	  

public:

	static void ClearVectors();

	static void ScanString(std::string inputString);
	static double DoTheMath();
	static double CalculateIt(std::string inputString);

};

#endif // !ARITHPROC_H_