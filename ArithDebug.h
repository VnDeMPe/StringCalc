#pragma once
#include "ArithProc.h"
#include <string>
class ArithDebug : public ArithProc
{
public:
	static void DebugDisplayValues();
	static void DebugDisplayString(std::string inputString);
};

