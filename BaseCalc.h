#pragma once
#ifndef  STRINGCALC_H_
#define  STRINGCALC_H_

#define StringCalcLib _declspec(dllexport)

#include <string>
#include <vector>

class  BaseCalc
{
private:
	static std::vector<std::string> _outputLogs;

protected:
	static std::vector<double> _arrayOfValues;
	static std::vector<char> _arrayOfOperators;
	static std::vector<int> _operatorPositionLvl1, _operatorPositionLvl2, _operatorPositionLvl3;

public: 
	static void AddToOutputLog(std::string Log);
	static std::vector<std::string> GetOutputLog();
	static void ClearOutputLog();
};


extern "C" {
	StringCalcLib double MarshalStringCalc(const char* pInputString, void (*addToList)(const char* pOutputString), int numFinDigital);

	StringCalcLib void intro();
}








#endif // ! STRINGCALC_H_
