#pragma once
#include "Arithmetic.h"
#include <iostream>
#include <vector>
#include <string>

class ArithProc : public Arithmetic
{
protected: // for debugger only 
	  //inline static std::list<double> stringValues;
	  //inline static std::list<char> stringOperands;
	  inline static std::vector<double> arrayOfValues;
	  inline static std::vector<char> arrayOfOperands;
	  inline static std::vector<int> charPositionLvl1, charPositionLvl2, charPositionLvl3;

public:
	static std::string RemoveSpaces(std::string inputString);
	static void ClearVectors();

	static void ScanString(std::string inputString);
	static double DoTheMath();
	static double CalculateIt(std::string inputString);

};

