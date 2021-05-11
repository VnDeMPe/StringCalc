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
	if (c == '+' || c == '*' || c == '/' || c == '^' || c == '$' || c == '-')
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
		unsigned int i;
		int openBrackets = 0;
		try
		{
			if (IsArithSymbol(inputString[0]) && inputString[0] != '-')  //if first digit is an operator add 0 
				throw (CalcFirstDigitException(__FILE__, __LINE__, __func__, inputString));
			if (inputString.size() == 0)
				throw (CalcException("An Empty string. ",__FILE__, __LINE__, __func__,  "0 has been returned."));
			
			for (i = 0; i < inputString.size(); i++)
			{
				if (isalpha(inputString[i]))
					throw (CalcFoundAlphaException(__FILE__, __LINE__, __func__, inputString, i));
				if (!isalnum(inputString[i]) && !IsAllowedSymbol(inputString[i]))
					throw (CalcNotAllowedCharException(__FILE__, __LINE__, __func__, inputString, i));
				if (IsSymbolTypoo(inputString[i], inputString[i + 1]))
					throw (CalcFoundTypooException(__FILE__, __LINE__, __func__, inputString, i));
				if ((IsArithSymbol(inputString[i]) || inputString[i] == '(') && (IsArithSymbol(inputString[i + 1]) && inputString[i + 1] != '-'))
					throw (CalcOperatorsSyntaxException(__FILE__, __LINE__, __func__, inputString, i));
				if (inputString[i]=='-' && inputString[i + 1] == '-')
					throw (CalcMinusSyntaxException(__FILE__, __LINE__, __func__, inputString, i));
				if (inputString[i] == '(' && inputString[i + 1] == ')')
					throw (CalcEmptyBracketsException(__FILE__, __LINE__, __func__, inputString, i));
				if (inputString[i] == '(') openBrackets++;
				else if (inputString[i] == ')') openBrackets--;
				if (openBrackets<0)
					throw (CalcBracketSyntaxException(__FILE__, __LINE__, __func__, inputString, i, openBrackets));
				if ((isdigit(inputString[i]) && inputString[i + 1] == '(') || ((inputString[i] == ')') && isdigit(inputString[i + 1])) ||(inputString[i]==')' && inputString[i + 1] == '('))  // if its '2(' or ')2' or ')('
					throw (ForceMultiply());
			}
			if (openBrackets > 0)
				throw (CalcBracketSyntaxException(__FILE__, __LINE__, __func__, inputString, i, openBrackets));


			if (IsArithSymbol(inputString[inputString.size()-1]))  //if the last char is an arithmetic symbol, erase it
				inputString.erase(inputString.size()-1, 1);

			syntaxErrorFound = false;
		}
		catch (CalcFirstDigitException& error)
		{
			CalcException::LogException(error);
			inputString.insert(0, "0"); //insert 0 at the begining
		}
		catch (CalcFoundAlphaException& error)
		{
			CalcException::LogException(error);
			inputString.erase(i, 1); //remove character
		}
		catch (CalcNotAllowedCharException& error)
		{
			CalcException::LogException(error);
			inputString.erase(i, 1); //remove character
		}
		catch (CalcFoundTypooException& error)
		{
			CalcException::LogException(error);
			inputString.erase(i, 1); //remove first symbol 
		}
		catch (CalcOperatorsSyntaxException& error)
		{
			CalcException::LogException(error);
			if (inputString[i] == '(')
				inputString.erase(i+1, 1); //remove second symbol
			else
				inputString.erase(i, 1); //remove first symbol 
		}
		catch (CalcMinusSyntaxException& error)
		{
			CalcException::LogException(error);
			inputString.erase(i, 2); //remove two minuses 
			inputString.insert(i, "+"); //replace it with plus
		}
		catch (CalcBracketSyntaxException& error)
		{
			CalcException::LogException(error);
			if (openBrackets < 0)
				inputString.erase(i, 1); //remove the bracket
			else
				inputString.push_back(')');
		}
		catch (CalcEmptyBracketsException& error)
		{
			CalcException::LogException(error);
			inputString.erase(i, 2); //remove pair of brackets
		}
		catch (ForceMultiply& error)
		{
			inputString.insert(i + 1, "*");
		}
		catch (CalcException& error)
		{
			CalcException::LogException(error);
			return "0";
		}
	}

	return inputString;
}

