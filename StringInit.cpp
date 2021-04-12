#include "StringInit.h"
#include "ArithDebug.h"
#include "CalcException.h"
#include <iostream>

std::string StringInit::RemoveSpaces(std::string inputString)  //	if there is space found, remove it. Afterwards erase left empty fields in the string
{
	inputString.erase(remove_if(inputString.begin(), inputString.end(), isspace), inputString.end());
	if (ArithDebug::IsDebugMode()) ArithDebug::DebugDisplayString(inputString, "Full string to be calculated:");
	return inputString;
}

bool StringInit::IsAllowedSymbol(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '$' || c == '.' || c == '(' || c == ')')
		return true;
	else
		return false;
}

bool StringInit::IsSymbolTypoo(char c1, char c2)
{
	if ((c1 == c2) && (c1 == '+' || c1 == '*' || c1 == '/' || c1 == '^' || c1 == '$' || c1 == '.'))
		return true;
	else
		return false;
}
std::string StringInit::CheckString(std::string inputString) //check integrity and syntax of the string
{
	bool syntaxErrorFound = true;
	int i;
	while (syntaxErrorFound)
	{
		try
		{
			if (!isdigit(inputString[0]) && inputString[0] != '(' && inputString[0] != '-')
				throw (CalcFirstDigitException(__FILE__, __LINE__, __func__, inputString));

			for (i = 0; i < inputString.size(); i++)
			{
				if (isalpha(inputString[i]))
					throw (CalcFoundAlphaException(__FILE__, __LINE__, __func__, inputString, i));
				if (!isalnum(inputString[i]) && !IsAllowedSymbol(inputString[i]))
					throw (CalcNotAllowedCharException(__FILE__, __LINE__, __func__, inputString, i));
				if (IsSymbolTypoo(inputString[i], inputString[i + 1]))
					throw (CalcFoundTypooException(__FILE__, __LINE__, __func__, inputString, i));
			}
			syntaxErrorFound = false;
		}
		catch (CalcFirstDigitException& error)
		{
			std::cout << error.what() << error.get_info() << std::endl;
			inputString.insert(0, "0"); //insert 0 at the end
		}
		catch (CalcFoundAlphaException& error)
		{
			std::cout << error.what() << error.get_info() << std::endl;
			inputString.erase(i, 1); //remove character
		}
		catch (CalcNotAllowedCharException& error)
		{
			std::cout << error.what() << error.get_info() << std::endl;
			inputString.erase(i, 1); //remove character
		}
		catch (CalcFoundTypooException& error)
		{
			std::cout << error.what() << error.get_info() << std::endl;
			inputString.erase(i, 1); //remove second symbol 
		}
	}

	return inputString;
}

std::string StringInit::StringInitiation(std::string inputString)
{
	std::string outputString;
	outputString = StringInit::RemoveSpaces(inputString);
	outputString = StringInit::CheckString(outputString);
	return outputString;
}