#pragma once
#ifndef ARITHPROC_H_
#define ARITHPROC_H_


#include "Arithmetic.h"
#include <iostream>
#include <vector>
#include <string>


class ArithProc : public Arithmetic
{
protected: 
	  //inline static std::list<double> stringValues;
	  //inline static std::list<char> stringOperands;
	  inline static std::vector<double> arrayOfValues;
	  inline static std::vector<char> arrayOfOperators;
	  inline static std::vector<int> OperatorPositionLvl1, OperatorPositionLvl2, OperatorPositionLvl3;
	  

public:
	static bool IsAllowedSymbol(char c);
	static bool IsSymbolTypoo(char c1, char c2);
	static std::string RemoveSpaces(std::string inputString);
	static std::string CheckString(std::string inputString);
	static void ClearVectors();

	static void ScanString(std::string inputString);
	static double DoTheMath();
	static double CalculateIt(std::string inputString);

};

#endif // !ARITHPROC_H_