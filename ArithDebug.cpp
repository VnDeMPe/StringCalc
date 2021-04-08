#include "ArithDebug.h"

//Class created only for Debug purposes. 

void ArithDebug::DebugDisplayValues() //Displays values and operands left in an array / vector
{
	for (int i = 0; i < arrayOfValues.size(); i++)
		std::cout << arrayOfValues[i] << " ";
	std::cout << std::endl;
	for (int i = 0; i < arrayOfOperands.size(); i++)
		std::cout << " " << arrayOfOperands[i];
	std::cout << std::endl;
}

void ArithDebug::DebugDisplayString(std::string inputString)
{
	std::cout << "String: " << inputString << std::endl;
}