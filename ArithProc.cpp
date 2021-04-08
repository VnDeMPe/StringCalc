#include "ArithProc.h"
#include "ArithDebug.h"
///////////Class designed to process and output the data///////////

//To do:
//Separate scanstring with process string. There should be separated methods. One for scan and save to vectors, and second for process the data.
//Add Brackets functionality 
//Add Multi-Brackets functionality
//Protect from stack overflow!!! 
//Clean the code, its getting messy




std::string ArithProc::RemoveSpaces(std::string inputString)  //	if there is space found, remove it. Afterwards erase left empty fields in the string
{
	inputString.erase(remove_if(inputString.begin(), inputString.end(), isspace), inputString.end());
	ArithDebug::DebugDisplayString(inputString,"Full string to be calculated:");
	return inputString;
}

void ArithProc::ScanString(std::string inputString) //	Scans the string, separates numbers and operators, saves it to the vector and calculates it. 
{
	ClearVectors();

	while (inputString.size() > 0)
	{
		int j = 0;
		if (isdigit(inputString[j]) || (inputString[j] == '.')) //	if its a digit, value is saved to the array. Afterwards digit in String is removed  
		{
			std::size_t digitEnd;
			double tempArg = std::stod(inputString, &digitEnd); 
			arrayOfValues.push_back(tempArg);
			inputString = inputString.substr(digitEnd);
		}
		else if (inputString[j] == '(')
		{
			for (int i = 0; i < inputString.size(); i++)
			{
				if (inputString[i] == ')')  //	if its a simple pair of brackets, store the current values and do the recursion 
				{
					std::string stringInBrackets = inputString.substr(1, i - 1);
					inputString.erase(inputString.begin(), inputString.begin() + i + 1);

					std::vector<double> tempValues = arrayOfValues;
					std::vector<char> tempOperands = arrayOfOperands;
					std::vector<int> tempPos1 = charPositionLvl1, tempPos2 = charPositionLvl2, tempPos3 = charPositionLvl3;

					ArithDebug::DebugDisplayString(stringInBrackets, "Found String in Brackets:");

					ScanString(stringInBrackets);
					charPositionLvl1 = tempPos1;
					charPositionLvl2 = tempPos2;
					charPositionLvl3 = tempPos3;
					tempValues.insert(tempValues.end(), arrayOfValues.begin(), arrayOfValues.end());
					arrayOfValues = tempValues;
					tempOperands.insert(tempOperands.end(), arrayOfOperands.begin(), arrayOfOperands.end());
					arrayOfOperands = tempOperands;

					ArithDebug::DebugDisplayValues("Array Values after solving brackets: (right side is not finished yet)");
				}
				else if (inputString[i] == '(') // next bracket found
				{
					// to be made 
				}
			}
		}
		else
		{
			arrayOfOperands.push_back(inputString[0]);

			if ((inputString[j] == '+') || (inputString[j] == '-'))
			{
				charPositionLvl3.push_back(arrayOfOperands.size() - 1);
			}
			else if ((inputString[j] == '*') || (inputString[j] == '/'))
			{
				charPositionLvl2.push_back(arrayOfOperands.size() - 1);
			}
			else if ((inputString[j] == '^') || (inputString[j] == '$'))
			{
				charPositionLvl1.push_back(arrayOfOperands.size() - 1);
			}

			inputString.erase(inputString.begin());
		}
	}

	double res = DoTheMath();
}


double ArithProc::DoTheMath()
{
	std::vector<double> notProcessedOperands, notProcessedValues; //Operands and numbers which were not processed yet 
	ArithDebug::DebugDisplayValues("Solving:");
	unsigned int numOp = 0;

	double result = 0;

	if (charPositionLvl1.size() > 0) //Power or sqrt 
	{
		for (int i = 0; i < charPositionLvl1.size(); i++)
		{
			charPositionLvl1[i] -= numOp;
			if (charPositionLvl1[i] < 0)
				charPositionLvl1[i] = 0;
			if (arrayOfOperands[charPositionLvl1[i]] == '^')
			{
				result = Power(arrayOfValues[charPositionLvl1[i]], static_cast<int>(arrayOfValues[charPositionLvl1[i] + 1]));
				arrayOfValues[charPositionLvl1[i]] = result;
				arrayOfValues.erase(arrayOfValues.begin() + charPositionLvl1[i] + 1);
				arrayOfOperands.erase(arrayOfOperands.begin() + charPositionLvl1[i]);
				numOp++;
				ArithDebug::DebugDisplayValues("Power done");
			}
			else if (arrayOfOperands[charPositionLvl1[i]] == '$')
			{
				result = Root(arrayOfValues[charPositionLvl1[i]], static_cast<int>(arrayOfValues[charPositionLvl1[i] + 1]));
				arrayOfValues[charPositionLvl1[i]] = result;
				arrayOfValues.erase(arrayOfValues.begin() + charPositionLvl1[i] + 1);
				arrayOfOperands.erase(arrayOfOperands.begin() + charPositionLvl1[i]);
				numOp++;
				ArithDebug::DebugDisplayValues("root done, result:");
			}
		}
	}
	if (charPositionLvl2.size() > 0) //Multiply or divide
	{
		for (int i = 0; i < arrayOfOperands.size(); i++)
		{
			if (arrayOfOperands[i] == '*')
			{
				result = Multiply(arrayOfValues[i], arrayOfValues[i + 1]);
				arrayOfValues[i] = result;
				arrayOfValues.erase(arrayOfValues.begin() + i + 1);
				arrayOfOperands.erase(arrayOfOperands.begin() + i);
				numOp++;
				i--;
				ArithDebug::DebugDisplayValues("multiply done, result:");
			}
			else if (arrayOfOperands[i] == '/')
			{
				result = Divide(arrayOfValues[i], arrayOfValues[i + 1]);
				arrayOfValues[i] = result;
				arrayOfValues.erase(arrayOfValues.begin() + i + 1);
				arrayOfOperands.erase(arrayOfOperands.begin() + i);
				numOp++;
				i--;
				ArithDebug::DebugDisplayValues("divide done, result:");
			}
		}
	}

	if (charPositionLvl3.size() > 0)	//add or substract 
	{

		for (int i = 0; i < charPositionLvl3.size(); i++)
		{
			charPositionLvl3[i] -= numOp;
			if (charPositionLvl3[i] < 0)
				charPositionLvl3[i] = 0;
			if (arrayOfOperands[charPositionLvl3[i]] == '+')
			{
				result = Add(arrayOfValues[charPositionLvl3[i]], arrayOfValues[charPositionLvl3[i] + 1]);
				arrayOfValues[charPositionLvl3[i]] = result;
				arrayOfValues.erase(arrayOfValues.begin() + charPositionLvl3[i] + 1);
				arrayOfOperands.erase(arrayOfOperands.begin() + charPositionLvl3[i]);
				numOp++;
				ArithDebug::DebugDisplayValues("add done, result:");
			}
			else if (arrayOfOperands[charPositionLvl3[i]] == '-')
			{
				result = Substract(arrayOfValues[charPositionLvl3[i]], arrayOfValues[charPositionLvl3[i] + 1]);
				arrayOfValues[charPositionLvl3[i]] = result;
				arrayOfValues.erase(arrayOfValues.begin() + charPositionLvl3[i] + 1);
				arrayOfOperands.erase(arrayOfOperands.begin() + charPositionLvl3[i]);
				numOp++;
				ArithDebug::DebugDisplayValues("substract done, result:");

			}
		}
		return result;
	}
}


double ArithProc::CalculateIt(std::string inputString)
{
	std::string outputString;
	outputString = ArithProc::RemoveSpaces(inputString);
	//check for brackets in // for loop? 
	// outputstring == string without brackets 
	// 2+2*2 for example
	// check for power or sqrt
	// check for multiply divide
	// 
	// 2+2+2
	// check for add minus
	// findPlusMinusOperand(string inputstring)

	std::size_t foundMultiplication = inputString.find("*");
	if (foundMultiplication != std::string::npos)
	{
		int i = 0;
		while (isdigit(inputString[foundMultiplication - i - 1]))
		{
			i++;
		}


		//int arg1 = std::stoi()

	}
	return 0;
}


void ArithProc::ClearVectors()
{
	arrayOfValues.clear();
	arrayOfOperands.clear();
	charPositionLvl1.clear();
	charPositionLvl2.clear();
	charPositionLvl3.clear();
}