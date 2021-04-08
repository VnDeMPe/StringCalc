#pragma once

#include "ArithProc.h"
#include <string>

class ArithDebug : public ArithProc
{
public:
	static void DebugDisplayValues();
	static void DebugDisplayValues(std::string comment);
	static void DebugDisplayString(std::string inputString);
	static void DebugDisplayString(std::string inputString, std::string comment);
};

