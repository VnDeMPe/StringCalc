#include "ArithProc.h"
#include "StringInit.h"
#include "ArithDebug.h"
#include "CalcException.h"
#include <iostream>
//Class designed to process and output the data

//To do:
//Separate scanstring with process string. There should be separated methods. One for scan and save to vectors, and second for process the data.
// The String to Arrays method would save only brackets positions. Then in calclulation i would start from last open bracket(vector<int>) to first close bracket(vector<int>)
//Protect from stack overflow
//Clean the code, its getting messy

double ArithProc::CalculateIt(std::string inputString)
{
	std::string outputString;
	outputString = StringInit::StringInitialization(inputString);
	std::cout << "Input String: " << outputString << std::endl;
	ArithProc::StringToArrays(outputString);
	std::cout << "The result is: " << arrayOfValues[0] << std::endl;

	return arrayOfValues[0];
}

void ArithProc::StringToArrays(std::string inputString) //	Scans the string, separates numbers and operators, saves it to the vector and calculates it. 
{
	ClearVectors();

	bool minusDigit = (inputString[0] == '-') ? true : false; //special exception for the first digit 

	while (inputString.size() > 0)
	{	
		if (isdigit(inputString[0]) || (inputString[0] == '.') || (minusDigit == true)) //	if its a digit, value is saved to an array. Afterwards digit in string is removed  
		{
			std::size_t digitEnd;
			double tempArg = std::stod(inputString, &digitEnd); 
			arrayOfValues.push_back(tempArg);
			inputString = inputString.substr(digitEnd);
			minusDigit = false;
		}
		else if (inputString[0] == '(')   //if there are brackets, they have to be solved first
		{
			std::vector<int> MultiBracketsPos;
			MultiBracketsPos.push_back(0); // first bracket is always on 0 position 
			unsigned int i = 1;

			while(MultiBracketsPos.size() > 0)	//while all brackets are not closed
			{
				if (inputString[i] == ')')  //	if its a simple pair of brackets, store the current values and do the recursion 
				{	
					int subStringLength = i-MultiBracketsPos.back() -1 ;	
					std::string stringInBrackets = inputString.substr(MultiBracketsPos.back() + 1, subStringLength);		 //  create a substring with data in brackets
					inputString.erase(inputString.begin() + MultiBracketsPos.back(), inputString.begin() + i + 1); //	 remove substring + brackets from main string 
					
					std::vector<double> tempValues = arrayOfValues;		// Temp-store arrays of processed data
					std::vector<char> tempOperators = arrayOfOperators;
					std::vector<int> tempPos1 = OperatorPositionLvl1, tempPos2 = OperatorPositionLvl2, tempPos3 = OperatorPositionLvl3;

					if (ArithDebug::IsDebugMode()) ArithDebug::DebugDisplayString(stringInBrackets, "Found String in Brackets:");

					StringToArrays(stringInBrackets);	 //Recurrence!

					if (MultiBracketsPos.size() > 1)  // if there are more brackets to close, put the iterator to the second-last bracket
					{
						i = MultiBracketsPos.end()[-2];		// end() is past the last element, -1 is for the last and -2 is for the second-last element
						inputString.insert(MultiBracketsPos.back(), std::to_string(arrayOfValues[0]));	// insert calculated value back to a string
						if (ArithDebug::IsDebugMode()) ArithDebug::DebugDisplayString(inputString, "My new string:");
					}

					else //if all brackets are closed, it is last while-loop cycle 
					{
						tempValues.push_back(arrayOfValues[0]); //push back the calculated value 
					}

					OperatorPositionLvl1 = tempPos1;  //saved arrays with position of operands 
					OperatorPositionLvl2 = tempPos2;
					OperatorPositionLvl3 = tempPos3;

					arrayOfValues = tempValues;
					arrayOfOperators = tempOperators;

					MultiBracketsPos.pop_back();	//erase the last element

					if (ArithDebug::IsDebugMode()) ArithDebug::DebugDisplayValues(arrayOfValues, arrayOfOperators,"Array Values after solving brackets: (right side is not finished yet)");
				}
				else if (inputString[i] == '(') // next bracket found
				{
					MultiBracketsPos.push_back(i);  // save the position of the open-bracket
				}

				i++;
			}
		} 
		else  if (!isalpha(inputString[0]))  // if its an operand add it to one of three arrays depend of the order of operations
		{
			arrayOfOperators.push_back(inputString[0]);

			if ((inputString[0] == '+') || (inputString[0] == '-'))
			{
				OperatorPositionLvl3.push_back(arrayOfOperators.size() - 1);
			}
			else if ((inputString[0] == '*') || (inputString[0] == '/'))
			{
				OperatorPositionLvl2.push_back(arrayOfOperators.size() - 1);
			}
			else if ((inputString[0] == '^') || (inputString[0] == '$'))
			{
				OperatorPositionLvl1.push_back(arrayOfOperators.size() - 1);
			}
			if (inputString.size() >= 2)
			if ((inputString[1] == '-') && (isdigit(inputString[2]) || (inputString[2] == '.')))  //  if the next value is minus digit
			{
				minusDigit = true;
			}
			inputString.erase(inputString.begin());
		}
	}

	double res = DoTheMath();
}


double ArithProc::DoTheMath()
{
	if (ArithDebug::IsDebugMode()) ArithDebug::DebugDisplayValues(arrayOfValues, arrayOfOperators, "Solving:");
	
	double result = 0;

	if (OperatorPositionLvl1.size() > 0) //if there is Power or sqrt operation
	{
		unsigned int numOp = 0;

		for (int i = 0; i < OperatorPositionLvl1.size(); i++)
		{
			OperatorPositionLvl1[i] -= numOp;

			if (arrayOfOperators[OperatorPositionLvl1[i]] == '^')
			{
				result = Power(arrayOfValues[OperatorPositionLvl1[i]], static_cast<int>(arrayOfValues[OperatorPositionLvl1[i] + 1]));
				arrayOfValues[OperatorPositionLvl1[i]] = result;
				arrayOfValues.erase(arrayOfValues.begin() + OperatorPositionLvl1[i] + 1);
				arrayOfOperators.erase(arrayOfOperators.begin() + OperatorPositionLvl1[i]);
				numOp++;
				if (ArithDebug::IsDebugMode()) ArithDebug::DebugDisplayValues(arrayOfValues, arrayOfOperators, "Power done");
			}
			else if (arrayOfOperators[OperatorPositionLvl1[i]] == '$')
			{
				result = Root(arrayOfValues[OperatorPositionLvl1[i]], static_cast<int>(arrayOfValues[OperatorPositionLvl1[i] + 1]));
				arrayOfValues[OperatorPositionLvl1[i]] = result;
				arrayOfValues.erase(arrayOfValues.begin() + OperatorPositionLvl1[i] + 1);
				arrayOfOperators.erase(arrayOfOperators.begin() + OperatorPositionLvl1[i]);
				numOp++;
				if (ArithDebug::IsDebugMode()) ArithDebug::DebugDisplayValues(arrayOfValues, arrayOfOperators, "root done, result:");
			}
		}
	}

	if (OperatorPositionLvl2.size() > 0) //If there is Multiply or divide operation
	{
		unsigned int i = 0;
		while( i < arrayOfOperators.size() )
		{
			if (arrayOfOperators[i] == '*')
			{
				result = Multiply(arrayOfValues[i], arrayOfValues[i + 1]);
				arrayOfValues[i] = result;
				arrayOfValues.erase(arrayOfValues.begin() + i + 1);
				arrayOfOperators.erase(arrayOfOperators.begin() + i);
				if (ArithDebug::IsDebugMode()) ArithDebug::DebugDisplayValues(arrayOfValues, arrayOfOperators, "multiply done, result:");
				continue;
			}
			else if (arrayOfOperators[i] == '/')
			{
				result = Divide(arrayOfValues[i], arrayOfValues[i + 1]);
				arrayOfValues[i] = result;
				arrayOfValues.erase(arrayOfValues.begin() + i + 1);
				arrayOfOperators.erase(arrayOfOperators.begin() + i);
				if (ArithDebug::IsDebugMode()) ArithDebug::DebugDisplayValues(arrayOfValues, arrayOfOperators, "divide done, result:");
				continue;
			}
			i++;
		}
	}

	if (OperatorPositionLvl3.size() > 0)	// If there is add or substract operation
	{
		while (arrayOfOperators.size() > 0)
		{
			if (arrayOfOperators[0] == '+')
			{
				result = Add(arrayOfValues[0], arrayOfValues[1]);
				arrayOfValues[0] = result;
				arrayOfValues.erase(arrayOfValues.begin() + 1);
				arrayOfOperators.erase(arrayOfOperators.begin());
				if (ArithDebug::IsDebugMode()) ArithDebug::DebugDisplayValues(arrayOfValues, arrayOfOperators, "add done, result:");
			}
			else if (arrayOfOperators[0] == '-')
			{
				result = Substract(arrayOfValues[0], arrayOfValues[1]);
				arrayOfValues[0] = result;
				arrayOfValues.erase(arrayOfValues.begin() + 1);
				arrayOfOperators.erase(arrayOfOperators.begin());
				if (ArithDebug::IsDebugMode()) ArithDebug::DebugDisplayValues(arrayOfValues, arrayOfOperators, "substract done, result:");
			}
		}
	}

	return result;
}

void ArithProc::ClearVectors()
{
	arrayOfValues.clear();
	arrayOfOperators.clear();
	OperatorPositionLvl1.clear();
	OperatorPositionLvl2.clear();
	OperatorPositionLvl3.clear();
}