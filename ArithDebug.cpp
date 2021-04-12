#include "ArithDebug.h"

//Class created only for Debug purposes. 

void ArithDebug::DebugDisplayValues(std::vector<double> inputDoubleVector, std::vector<char> inputCharVector) //Displays values and operands left in an array / vector
{
	for (int i = 0; i < inputDoubleVector.size(); i++)
	{
		std::cout << inputDoubleVector[i] << " ";
		if (i < inputCharVector.size())
			std::cout << inputCharVector[i] << " ";
	}
	std::cout << std::endl;
}

void ArithDebug::DebugDisplayValues(std::vector<double> inputDoubleVector, std::vector<char> inputCharVector, std::string comment)
{
	std::cout << comment << std::endl; 
	for (int i = 0; i < inputDoubleVector.size(); i++)
	{
		std::cout << inputDoubleVector[i] << " ";
		if (i < inputCharVector.size())
		std::cout  << inputCharVector[i] << " ";
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