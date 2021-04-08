#include "ArithProc.h"
//Class designed to process and output the data

//To do:
//Separate scanstring with process string. There should be separated methods. One for scan and save to vectors, and second for process the data.
//Add Brackets functionality 
//Add Multi-Brackets functionality
//Protect from stack overflow!!! 
//Clean the code, its getting messy

std::string ArithProc::RemoveSpaces(std::string inputString)
{
	inputString.erase(remove_if(inputString.begin(), inputString.end(), isspace), inputString.end());
	return inputString;
}

void ArithProc::ScanString(std::string inputString) //
{
	ClearVectors();
	double tempArg;
	while (inputString.size() > 0)
	{
		int j = 0;
		if (isdigit(inputString[j]) || (inputString[j] == '.')) // || ((inputString[j] == '-') && (!isdigit(inputString[j+1]))))
		{
			while (isdigit(inputString[j]) || (inputString[j] == '.'))
				j++;
			std::size_t digitEnd;
			tempArg = std::stod(inputString, &digitEnd);
			arrayOfValues.push_back(tempArg);
			inputString = inputString.substr(digitEnd);
		}
		else if (inputString[j] == '(')
		{
			// Not finished! Don't go there yet. 
			std::cout << "Brackets! Not coded" << std::endl; 

			
			//while ) or (  -> if ) - ble ble // else if ( - ble bleh 
			//if its ) then its ez
			//i cut the string and calculate it already?
			//i mean what is the other choice
			// but i wanted separately scan string and save it to the array
			// and this way i have to calculate the full array
			
			inputString.erase(inputString.begin());
			std::vector<double> tempValues = arrayOfValues;
			std::vector<char> tempOperands = arrayOfOperands;
			ScanString("7+7+7");
			arrayOfValues.insert(arrayOfValues.end(), tempValues.begin(), tempValues.end());
			arrayOfOperands.insert(arrayOfOperands.end(), tempOperands.begin(), tempOperands.end());
			
			//stringValues.splice(stringValues.begin(), tempValues);
			//stringOperands.splice(stringOperands.begin(), tempOperands);

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
	int res = DoTheMath();
	std::cout << res << std::endl;
	//	displayValues();
}


double ArithProc::DoTheMath()
{
	std::vector<double> notProcessedOperands, notProcessedValues; //Operands and numbers which were not processed yet 

	unsigned int numOp = 0;

	double result = 0;
	std::cout << "Sizes powersqrt : " << charPositionLvl1.size() << std::endl;
	std::cout << "Sizes muldidivide : " << charPositionLvl2.size() << std::endl;
	std::cout << "Sizes plusminus : " << charPositionLvl3.size() << std::endl;

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
				//ArithDebug::DebugDisplayValues();
			}
			else if (arrayOfOperands[charPositionLvl1[i]] == '$')
			{
				result = Root(arrayOfValues[charPositionLvl1[i]], static_cast<int>(arrayOfValues[charPositionLvl1[i] + 1]));
				arrayOfValues[charPositionLvl1[i]] = result;
				arrayOfValues.erase(arrayOfValues.begin() + charPositionLvl1[i] + 1);
				arrayOfOperands.erase(arrayOfOperands.begin() + charPositionLvl1[i]);
				numOp++;
				//ArithDebug::DebugDisplayValues();
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
				//ArithDebug::DebugDisplayValues();
			}
			else if (arrayOfOperands[i] == '/')
			{
				result = Divide(arrayOfValues[i], arrayOfValues[i + 1]);
				arrayOfValues[i] = result;
				arrayOfValues.erase(arrayOfValues.begin() + i + 1);
				arrayOfOperands.erase(arrayOfOperands.begin() + i);
				numOp++;
				i--;
				//ArithDebug::DebugDisplayValues();
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
				//ArithDebug::DebugDisplayValues();
			}
			else if (arrayOfOperands[charPositionLvl3[i]] == '-')
			{
				result = Substract(arrayOfValues[charPositionLvl3[i]], arrayOfValues[charPositionLvl3[i] + 1]);
				arrayOfValues[charPositionLvl3[i]] = result;
				arrayOfValues.erase(arrayOfValues.begin() + charPositionLvl3[i] + 1);
				arrayOfOperands.erase(arrayOfOperands.begin() + charPositionLvl3[i]);
				numOp++;
				//ArithDebug::DebugDisplayValues();

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