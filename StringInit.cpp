#include "StringInit.h"
#include "ArithDebug.h"
#include "CalcException.h"
#include <iostream>

// Class which prepares the string before the arithmetic calculations.

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

bool StringInit::IsArithSymbol(char c)
{
	if (c == '+' || c == '*' || c == '/' || c == '^' || c == '$')
		return true;
	else
		return false;
}

bool StringInit::IsBracket(char c)
{
	return (c == '(' || c == ')') ? true : false;
}

std::string StringInit::StringInitialization(std::string inputString)
{
	std::string outputString;
	outputString = StringInit::RemoveSpaces(inputString);
	outputString = StringInit::CheckString(outputString);
	return outputString;
}

std::string StringInit::RemoveSpaces(std::string inputString)  //	if there is space found, remove it. Afterwards erase left empty fields in the string
{
	inputString.erase(remove_if(inputString.begin(), inputString.end(), isspace), inputString.end());
	if (ArithDebug::IsDebugMode()) ArithDebug::DebugDisplayString(inputString, "Full string to be calculated:");
	return inputString;
}

std::string StringInit::CheckString(std::string inputString) //check integrity and syntax of the string
{
	bool syntaxErrorFound = true;
	
	while (syntaxErrorFound)
	{
		int i, openBrackets = 0;
		try
		{
			if (IsArithSymbol(inputString[0]))  //if first digit is an operator add 0 
				throw (CalcFirstDigitException(__FILE__, __LINE__, __func__, inputString));
			if (inputString.size() == 0)
				throw (CalcException("An Empty string. ",__FILE__, __LINE__, __func__,  "0 has been returned."));
			
			for (i = 0; i < inputString.size(); i++)
			{
				if ((isdigit(inputString[i]) && inputString[i + 1] == '(') || ((inputString[i] == ')') && isdigit(inputString[i + 1])))
					throw (ForceMultiply());
				if (isalpha(inputString[i]))
					throw (CalcFoundAlphaException(__FILE__, __LINE__, __func__, inputString, i));
				if (!isalnum(inputString[i]) && !IsAllowedSymbol(inputString[i]))
					throw (CalcNotAllowedCharException(__FILE__, __LINE__, __func__, inputString, i));
				if (IsSymbolTypoo(inputString[i], inputString[i + 1]))
					throw (CalcFoundTypooException(__FILE__, __LINE__, __func__, inputString, i));
				if (IsArithSymbol(inputString[i]) && IsArithSymbol(inputString[i + 1]))
					throw (CalcOperatorsSyntaxException(__FILE__, __LINE__, __func__, inputString, i));
				if (inputString[i]=='-' && inputString[i+1] == '-')
					throw (CalcMinusSyntaxException(__FILE__, __LINE__, __func__, inputString, i));
				if (inputString[i] == '(') openBrackets++;
				if (inputString[i] == ')') openBrackets--;
				if (openBrackets<0)
					throw (CalcBracketSyntaxException(__FILE__, __LINE__, __func__, inputString, i, openBrackets));
			}
			if (openBrackets > 0)
				throw (CalcBracketSyntaxException(__FILE__, __LINE__, __func__, inputString, i, openBrackets));
			syntaxErrorFound = false;
		}
		catch (CalcFirstDigitException& error)
		{
			std::cout << error.what() << error.get_info() << std::endl;
			inputString.insert(0, "0"); //insert 0 at the begining
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
		catch (CalcOperatorsSyntaxException& error)
		{
			std::cout << error.what() << error.get_info() << std::endl;
			inputString.erase(i, 1); //remove second symbol 
		}
		catch (CalcMinusSyntaxException& error)
		{
			std::cout << error.what() << error.get_info() << std::endl;
			inputString.erase(i, 2); //remove two minuses 
			inputString.insert(i, "+"); //replace it with plus
		}
		catch (CalcBracketSyntaxException& error)
		{
			std::cout << error.what() << error.get_info() << std::endl;
			if (openBrackets < 0)
				inputString.erase(i, 1); //remove the bracket
			else
				inputString.push_back(')');
		}
		catch (ForceMultiply& error)
		{
			inputString.insert(i+1, "*");
		}
		catch (CalcException& error)
		{
			std::cout << error.what() << error.get_info() << std::endl;
			return "0";
		}
	}

	return inputString;
}

