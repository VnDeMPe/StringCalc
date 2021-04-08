#include "ArithDebug.h"

//Class created only for Debug purposes. 

void ArithDebug::DebugDisplayValues() //Displays values and operands left in an array / vector
{
	for (int i = 0; i < arrayOfValues.size(); i++)
	{
		std::cout << arrayOfValues[i] << " ";
		if (i < arrayOfOperands.size())
			std::cout << arrayOfOperands[i] << " ";
	}
	std::cout << std::endl;
}

void ArithDebug::DebugDisplayValues(std::string comment) 
{
	std::cout << comment << std::endl; 
	for (int i = 0; i < arrayOfValues.size(); i++) 
	{
		std::cout << arrayOfValues[i] << " ";
		if (i < arrayOfOperands.size())
		std::cout  << arrayOfOperands[i] << " ";
	}
	std::cout << std::endl;
}


void ArithDebug::DebugDisplayString(std::string inputString)
{
	std::cout << "Input String: " << inputString << std::endl;
}

void ArithDebug::DebugDisplayString(std::string inputString, std::string comment)
{
	std::cout << comment << std::endl << inputString << std::endl;
}