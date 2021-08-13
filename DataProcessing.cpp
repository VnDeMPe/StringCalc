#include "DataProcessing.h"
#include "StringInit.h"
#include "ArithDebug.h" 
#include <iostream>
//Class designed to process and output the data

//To do:
//Separate scanstring with process string. There should be separated methods. One for scan and save to vectors, and second for process the data.
// The String to Arrays method would save only brackets positions. Then in calclulation i would start from last open bracket(vector<int>) to first close bracket(vector<int>)
//Protect from stack overflow
//Clean the code, its getting messy

double DataProcessing::CalculateIt(std::string inputString, std::string& preparedString, int numFinalDecimals)
{
	std::string outputString;
	outputString = StringInit::StringInitialization(inputString);
	preparedString = outputString;
	double result = DataProcessing::StringToArrays(outputString);
	result = Round(result, true, numFinalDecimals);

	return result;
}

double DataProcessing::StringToArrays(std::string inputString) //	Scans the string, separates numbers and operators, saves it to the vector and calculates it. 
{
	ClearVectors();

	bool minusDigit = (inputString[0] == '-') ? true : false; //special exception for the first digit 

	while (inputString.size() > 0)
	{	
		if (isdigit(inputString[0]) || (inputString[0] == '.') || (minusDigit == true)) //	if its a digit, value is saved to an array. Afterwards digit in string is removed  
		{
			std::size_t digitEnd;
			double tempArg = std::stod(inputString, &digitEnd); 
			_arrayOfValues.push_back(tempArg);
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
					
					std::vector<double> tempValues = _arrayOfValues;		// Temp-store arrays of processed data
					std::vector<char> tempOperators = _arrayOfOperators;
					std::vector<int> tempPos1 = _operatorPositionLvl1, tempPos2 = _operatorPositionLvl2, tempPos3 = _operatorPositionLvl3;

					if (ArithDebug::IsDebugMode()) ArithDebug::DebugDisplayString(stringInBrackets, "Found String in Brackets:");

					StringToArrays(stringInBrackets);	 //Recurrence!

					if (MultiBracketsPos.size() > 1)  // if there are more brackets to close, put the iterator to the second-last bracket
					{
						i = MultiBracketsPos.end()[-2];		// end() is past the last element, -1 is for the last and -2 is for the second-last element
						inputString.insert(MultiBracketsPos.back(), std::to_string(_arrayOfValues[0]));	// insert calculated value back to a string
						if (ArithDebug::IsDebugMode()) ArithDebug::DebugDisplayString(inputString, "My new string:");
					}

					else //if all brackets are closed, it is last while-loop cycle 
					{
						tempValues.push_back(_arrayOfValues[0]); //push back the calculated value 
					}

					_operatorPositionLvl1 = tempPos1;  //saved arrays with position of operands 
					_operatorPositionLvl2 = tempPos2;
					_operatorPositionLvl3 = tempPos3;

					_arrayOfValues = tempValues;
					_arrayOfOperators = tempOperators;

					MultiBracketsPos.pop_back();	//erase the last element

					if (ArithDebug::IsDebugMode()) ArithDebug::DebugDisplayValues(_arrayOfValues, _arrayOfOperators,"Array Values after solving brackets: (right side is not finished yet)");
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
			_arrayOfOperators.push_back(inputString[0]);

			if ((inputString[0] == '+') || (inputString[0] == '-'))
			{
				_operatorPositionLvl3.push_back(_arrayOfOperators.size() - 1);
			}
			else if ((inputString[0] == '*') || (inputString[0] == '/'))
			{
				_operatorPositionLvl2.push_back(_arrayOfOperators.size() - 1);
			}
			else if ((inputString[0] == '^') || (inputString[0] == '$'))
			{
				_operatorPositionLvl1.push_back(_arrayOfOperators.size() - 1);
			}
			if (inputString.size() >= 2)
			if ((inputString[1] == '-') && (isdigit(inputString[2]) || (inputString[2] == '.')))  //  if the next value is minus digit
			{
				minusDigit = true;
			}
			inputString.erase(inputString.begin());
		}
	}

	double result = DoTheMath();
	return result;
}


double DataProcessing::DoTheMath()
{
	if (ArithDebug::IsDebugMode()) ArithDebug::DebugDisplayValues(_arrayOfValues, _arrayOfOperators, "Solving:");
	
	double result = 0;

	if (_operatorPositionLvl1.size() > 0) //if there is Power or sqrt operation
	{
		unsigned int numOp = 0;

		for (int i = 0; i < _operatorPositionLvl1.size(); i++)
		{
			_operatorPositionLvl1[i] -= numOp;

			if (_arrayOfOperators[_operatorPositionLvl1[i]] == '^')
			{
				result = Power(_arrayOfValues[_operatorPositionLvl1[i]], static_cast<int>(_arrayOfValues[_operatorPositionLvl1[i] + 1]));
				_arrayOfValues[_operatorPositionLvl1[i]] = result;
				_arrayOfValues.erase(_arrayOfValues.begin() + _operatorPositionLvl1[i] + 1);
				_arrayOfOperators.erase(_arrayOfOperators.begin() + _operatorPositionLvl1[i]);
				numOp++;
				if (ArithDebug::IsDebugMode()) ArithDebug::DebugDisplayValues(_arrayOfValues, _arrayOfOperators, "Power done");
			}
			else if (_arrayOfOperators[_operatorPositionLvl1[i]] == '$')
			{
				result = Root(_arrayOfValues[_operatorPositionLvl1[i]], static_cast<int>(_arrayOfValues[_operatorPositionLvl1[i] + 1]));
				_arrayOfValues[_operatorPositionLvl1[i]] = result;
				_arrayOfValues.erase(_arrayOfValues.begin() + _operatorPositionLvl1[i] + 1);
				_arrayOfOperators.erase(_arrayOfOperators.begin() + _operatorPositionLvl1[i]);
				numOp++;
				if (ArithDebug::IsDebugMode()) ArithDebug::DebugDisplayValues(_arrayOfValues, _arrayOfOperators, "root done, result:");
			}
		}
	}

	if (_operatorPositionLvl2.size() > 0) //If there is Multiply or divide operation
	{
		unsigned int i = 0;
		while( i < _arrayOfOperators.size() )
		{
			if (_arrayOfOperators[i] == '*')
			{
				result = Multiply(_arrayOfValues[i], _arrayOfValues[i + 1]);
				_arrayOfValues[i] = result;
				_arrayOfValues.erase(_arrayOfValues.begin() + i + 1);
				_arrayOfOperators.erase(_arrayOfOperators.begin() + i);
				if (ArithDebug::IsDebugMode()) ArithDebug::DebugDisplayValues(_arrayOfValues, _arrayOfOperators, "multiply done, result:");
				continue;
			}
			else if (_arrayOfOperators[i] == '/')
			{
				result = Divide(_arrayOfValues[i], _arrayOfValues[i + 1]);
				_arrayOfValues[i] = result;
				_arrayOfValues.erase(_arrayOfValues.begin() + i + 1);
				_arrayOfOperators.erase(_arrayOfOperators.begin() + i);
				if (ArithDebug::IsDebugMode()) ArithDebug::DebugDisplayValues(_arrayOfValues, _arrayOfOperators, "divide done, result:");
				continue;
			}
			i++;
		}
	}

	if (_operatorPositionLvl3.size() > 0)	// If there is add or substract operation
	{
		while (_arrayOfOperators.size() > 0)
		{
			if (_arrayOfOperators[0] == '+')
			{
				result = Add(_arrayOfValues[0], _arrayOfValues[1]);
				_arrayOfValues[0] = result;
				_arrayOfValues.erase(_arrayOfValues.begin() + 1);
				_arrayOfOperators.erase(_arrayOfOperators.begin());
				if (ArithDebug::IsDebugMode()) ArithDebug::DebugDisplayValues(_arrayOfValues, _arrayOfOperators, "add done, result:");
			}
			else if (_arrayOfOperators[0] == '-')
			{
				result = Substract(_arrayOfValues[0], _arrayOfValues[1]);
				_arrayOfValues[0] = result;
				_arrayOfValues.erase(_arrayOfValues.begin() + 1);
				_arrayOfOperators.erase(_arrayOfOperators.begin());
				if (ArithDebug::IsDebugMode()) ArithDebug::DebugDisplayValues(_arrayOfValues, _arrayOfOperators, "substract done, result:");
			}
		}
	}

	return _arrayOfValues[0];
}

void DataProcessing::ClearVectors()
{
	_arrayOfValues.clear();
	_arrayOfOperators.clear();
	_operatorPositionLvl1.clear();
	_operatorPositionLvl2.clear();
	_operatorPositionLvl3.clear();
}