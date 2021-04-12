#pragma once
#ifndef STRINGINIT_H_
#define STRINGINIT_H_

#include <string>

class StringInit
{
public:
	static bool IsAllowedSymbol(char c);
	static bool IsArithSymbol(char c);
	static bool IsSymbolTypoo(char c1, char c2);
	
	static std::string StringInitiation(std::string inputString);
	static std::string RemoveSpaces(std::string inputString);
	static std::string CheckString(std::string inputString);
};


#endif // ! STRINGINIT_H_