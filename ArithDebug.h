#pragma once
#ifndef ARITHDEBUG_H_
#define ARITHDEBUG_H_

#include <string>
#include <vector>

class ArithDebug
{
private:
	static bool _debugMode;
public:
	static void SetDebugMode(bool isDebug);
	static bool IsDebugMode();
	static void DebugDisplayValues(std::vector<double> inputDoubleVector, std::vector<char> inputCharVector);
	static void DebugDisplayValues(std::vector<double> inputDoubleVector, std::vector<char> inputCharVector, std::string comment);
	static void DebugDisplayString(std::string inputString);
	static void DebugDisplayString(std::string inputString, std::string comment);
};

#endif // !ARITHDEBUG_H_
