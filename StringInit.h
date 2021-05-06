#pragma once
#ifndef STRINGINIT_H_
#define STRINGINIT_H_

#include "BaseCalc.h"

class StringInit : BaseCalc
{
public:
	static bool IsAllowedSymbol(char c);
	static bool IsArithSymbol(char c);
	static bool IsSymbolTypoo(char c1, char c2);
	static bool IsBracket(char c);
	
	static std::string StringInitialization(std::string inputString);
	static std::string RemoveSpaces(std::string inputString);
	static std::string CheckString(std::string inputString);
};


#endif // ! STRINGINIT_H_