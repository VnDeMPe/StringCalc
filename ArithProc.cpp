#include "ArithProc.h"
#include "ArithDebug.h"
///////////Class designed to process and output the data///////////

//To do:
//Separate scanstring with process string. There should be separated methods. One for scan and save to vectors, and second for process the data.
//Protect from stack overflow!!! 
//Clean the code, its getting messy! 


bool debugMode = false;

std::string ArithProc::RemoveSpaces(std::string inputString)  //	if there is space found, remove it. Afterwards erase left empty fields in the string
{
	inputString.erase(remove_if(inputString.begin(), inputString.end(), isspace), inputString.end());
	if (debugMode) ArithDebug::DebugDisplayString(inputString,"Full string to be calculated:");
	return inputString;
}

void ArithProc::ScanString(std::string inputString) //	Scans the string, separates numbers and operators, saves it to the vector and calculates it. 
{
	ClearVectors();

	bool minusDigit = false;
	if (inputString[0] == '-')	//special exception for the first digit 
		minusDigit = true; 

	while (inputString.size() > 0)
	{
		int j = 0;
		
		if (isdigit(inputString[j]) || (inputString[j] == '.') || (minusDigit == true)) //	if its a digit, value is saved to the array. Afterwards digit in String is removed  
		{
			std::size_t digitEnd;
			double tempArg = std::stod(inputString, &digitEnd); 
			arrayOfValues.push_back(tempArg);
			inputString = inputString.substr(digitEnd);
			minusDigit = false;
		}
		else if (inputString[j] == '(')
		{
		
			std::vector<int> MultiBracketsPos;
			MultiBracketsPos.push_back(0); // first bracket is always on 0 position 
			for (int i = 1; i < inputString.size(); i++)
			{
				if (inputString[i] == ')')  //	if its a simple pair of brackets, store the current values and do the recursion 
				{

					std::string stringInBrackets = inputString.substr(MultiBracketsPos.back() + 1, i - MultiBracketsPos.size());		 //  create a substring 
					inputString.erase(inputString.begin() + MultiBracketsPos.back(), inputString.begin() + i + 1); //	 remove substring + brackets from main string 
					
					std::vector<double> tempValues = arrayOfValues;
					std::vector<char> tempOperators = arrayOfOperators;
					std::vector<int> tempPos1 = OperatorPositionLvl1, tempPos2 = OperatorPositionLvl2, tempPos3 = OperatorPositionLvl3;

					if (debugMode) ArithDebug::DebugDisplayString(stringInBrackets, "Found String in Brackets:");

					ScanString(stringInBrackets);

					if (MultiBracketsPos.size() > 1)  //more brackets to close
					{
						i = 0;
						inputString.insert(MultiBracketsPos.back(), std::to_string(arrayOfValues[0]));
						if (debugMode) ArithDebug::DebugDisplayString(inputString, "My new string:");
					}

					else // all brackets closed 
					{
						i = inputString.size();
						tempValues.push_back(arrayOfValues[0]); //push back the calculated value 
					}

					OperatorPositionLvl1 = tempPos1;  //saved arrays with position of operands 
					OperatorPositionLvl2 = tempPos2;
					OperatorPositionLvl3 = tempPos3;

					arrayOfValues = tempValues;
					arrayOfOperators = tempOperators;

					MultiBracketsPos.pop_back();
					if (debugMode) ArithDebug::DebugDisplayValues("Array Values after solving brackets: (right side is not finished yet)");
				}
				else if (inputString[i] == '(') // next bracket found
				{
					MultiBracketsPos.push_back(i);  // save the position of open bracket
				}
			}
		} 
		else  if (!isalpha(inputString[j]))  // if its an operand add it to one of three arrays depend of the order of operations
		{
			arrayOfOperators.push_back(inputString[0]);

			if ((inputString[j] == '+') || (inputString[j] == '-'))
			{
				OperatorPositionLvl3.push_back(arrayOfOperators.size() - 1);
			}
			else if ((inputString[j] == '*') || (inputString[j] == '/'))
			{
				OperatorPositionLvl2.push_back(arrayOfOperators.size() - 1);
			}
			else if ((inputString[j] == '^') || (inputString[j] == '$'))
			{
				OperatorPositionLvl1.push_back(arrayOfOperators.size() - 1);
			}
			if (inputString.size() >= 2)
			if ((inputString[j + 1] == '-') && (isdigit(inputString[j+2]) || (inputString[j+2] == '.')))  //  if the next value is minus digit
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
	std::vector<double> notProcessedOperands, notProcessedValues; //Operands and numbers which were not processed yet 
	if (debugMode) ArithDebug::DebugDisplayValues("Solving:");
	unsigned int numOp = 0;

	double result = 0;

	if (OperatorPositionLvl1.size() > 0) //Power or sqrt 
	{
		for (int i = 0; i < OperatorPositionLvl1.size(); i++)
		{
			OperatorPositionLvl1[i] -= numOp;
			if (OperatorPositionLvl1[i] < 0)
				OperatorPositionLvl1[i] = 0;
			if (arrayOfOperators[OperatorPositionLvl1[i]] == '^')
			{
				result = Power(arrayOfValues[OperatorPositionLvl1[i]], static_cast<int>(arrayOfValues[OperatorPositionLvl1[i] + 1]));
				arrayOfValues[OperatorPositionLvl1[i]] = result;
				arrayOfValues.erase(arrayOfValues.begin() + OperatorPositionLvl1[i] + 1);
				arrayOfOperators.erase(arrayOfOperators.begin() + OperatorPositionLvl1[i]);
				numOp++;
				if (debugMode) ArithDebug::DebugDisplayValues("Power done");
			}
			else if (arrayOfOperators[OperatorPositionLvl1[i]] == '$')
			{
				result = Root(arrayOfValues[OperatorPositionLvl1[i]], static_cast<int>(arrayOfValues[OperatorPositionLvl1[i] + 1]));
				arrayOfValues[OperatorPositionLvl1[i]] = result;
				arrayOfValues.erase(arrayOfValues.begin() + OperatorPositionLvl1[i] + 1);
				arrayOfOperators.erase(arrayOfOperators.begin() + OperatorPositionLvl1[i]);
				numOp++;
				if (debugMode) ArithDebug::DebugDisplayValues("root done, result:");
			}
		}
	}

	if (OperatorPositionLvl2.size() > 0) //Multiply or divide
	{
		for (int i = 0; i < arrayOfOperators.size(); i++)
		{
			if (arrayOfOperators[i] == '*')
			{
				result = Multiply(arrayOfValues[i], arrayOfValues[i + 1]);
				arrayOfValues[i] = result;
				arrayOfValues.erase(arrayOfValues.begin() + i + 1);
				arrayOfOperators.erase(arrayOfOperators.begin() + i);
				numOp++;
				i--;
				if (debugMode) ArithDebug::DebugDisplayValues("multiply done, result:");
			}
			else if (arrayOfOperators[i] == '/')
			{
				result = Divide(arrayOfValues[i], arrayOfValues[i + 1]);
				arrayOfValues[i] = result;
				arrayOfValues.erase(arrayOfValues.begin() + i + 1);
				arrayOfOperators.erase(arrayOfOperators.begin() + i);
				numOp++;
				i--;
				if (debugMode) ArithDebug::DebugDisplayValues("divide done, result:");
			}
		}
	}

	if (OperatorPositionLvl3.size() > 0)	//add or substract 
	{

		for (int i = 0; i < OperatorPositionLvl3.size(); i++)
		{
			OperatorPositionLvl3[i] -= numOp;
			if (OperatorPositionLvl3[i] < 0)
				OperatorPositionLvl3[i] = 0;
			if (arrayOfOperators[OperatorPositionLvl3[i]] == '+')
			{
				result = Add(arrayOfValues[OperatorPositionLvl3[i]], arrayOfValues[OperatorPositionLvl3[i] + 1]);
				arrayOfValues[OperatorPositionLvl3[i]] = result;
				arrayOfValues.erase(arrayOfValues.begin() + OperatorPositionLvl3[i] + 1);
				arrayOfOperators.erase(arrayOfOperators.begin() + OperatorPositionLvl3[i]);
				numOp++;
				if (debugMode) ArithDebug::DebugDisplayValues("add done, result:");
			}
			else if (arrayOfOperators[OperatorPositionLvl3[i]] == '-')
			{
				result = Substract(arrayOfValues[OperatorPositionLvl3[i]], arrayOfValues[OperatorPositionLvl3[i] + 1]);
				arrayOfValues[OperatorPositionLvl3[i]] = result;
				arrayOfValues.erase(arrayOfValues.begin() + OperatorPositionLvl3[i] + 1);
				arrayOfOperators.erase(arrayOfOperators.begin() + OperatorPositionLvl3[i]);
				numOp++;
				if (debugMode) ArithDebug::DebugDisplayValues("substract done, result:");

			}
		}
		return result;
	}
}


double ArithProc::CalculateIt(std::string inputString)
{
	std::string outputString;
	outputString = ArithProc::RemoveSpaces(inputString);
	std::cout << "Input String: " << outputString << std::endl;
	ArithProc::ScanString(outputString);
	std::cout << "The result is: " << arrayOfValues[0] << std::endl; 
	
	return 0;
}


void ArithProc::ClearVectors()
{
	arrayOfValues.clear();
	arrayOfOperators.clear();
	OperatorPositionLvl1.clear();
	OperatorPositionLvl2.clear();
	OperatorPositionLvl3.clear();
}