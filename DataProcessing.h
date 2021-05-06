#pragma once
#ifndef ARITHPROC_H_
#define ARITHPROC_H_


#include "Arithmetic.h"
#include <vector>
#include <string>

//getters setters


class DataProcessing : public Arithmetic
{
private: 
	  //inline static std::list<double> stringValues;
	  //inline static std::list<char> stringOperands;

	  

public:

	static void ClearVectors();

	static double StringToArrays(std::string inputString);
	static double DoTheMath();
	static double CalculateIt(std::string inputString);

};

#endif // !ARITHPROC_H_