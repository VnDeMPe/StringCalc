#include "CalcException.h"
#include <iostream>

//Handling Exception Classes 

const char* CalcException::get_file() const 
{
	return file; 
}
int CalcException::get_line() const 
{ 
	return line; 
}
const char* CalcException::get_func() const 
{ 
	return func; 
}

std::string CalcException::get_info() const 
{ 
	return info; 
}

void CalcException::DispException()
{
	std::cout <<"\nException occured in file " <<get_file() << " in Function: " << get_func() << " at line nr " <<get_line() << std::endl;
}

CalcException::CalcException(const char* msg, const char* file_, int line_, const char* func_, std::string info_ = "Errore") : std::runtime_error(msg),
file(file_),
line(line_),
func(func_),
info(info_)
{
	DispException();
}

CalcException::CalcException() : std::runtime_error("err")
{
}


std::string CalcZeroException::get_info() const 
{ 
	return (info + ": 0 has been changed to 1"); 
}


CalcZeroException::CalcZeroException(const char* file_, int line_, const char* func_, double arg1_, double arg2_) : CalcException("Math Error: Not allowed to divide by zero\n", file_, line_, func_, ("Attempt to divide " + std::to_string(arg1_) + " with " + std::to_string(arg2_)) ),
arg1(arg1_),
arg2(arg2_)
{
}

CalcFirstDigitException::CalcFirstDigitException(const char* file_, int line_, const char* func_, std::string arg1_) : CalcException("Syntax Error: Missing first digit\n", file_, line_, func_, ("No digit on the left side of operation: '" + arg1_.substr(0,2) )),
arg1(arg1_)
{
}

std::string CalcFirstDigitException::get_info() const
{
	return (info + "'. 0 added as first digit");
}

CalcFoundAlphaException::CalcFoundAlphaException(const char* file_, int line_, const char* func_, std::string arg1_, int i_) : CalcException("Syntax Error: Found alphabet letter\n", file_, line_, func_, ("Alphabet character found: '" + arg1_.substr(i_, 1))),
arg1(arg1_),
i(i_)
{
}

std::string CalcFoundAlphaException::get_info() const
{
	return (info + "' at position " + std::to_string(i) + ". Character has been removed");
}

CalcNotAllowedCharException::CalcNotAllowedCharException(const char* file_, int line_, const char* func_, std::string arg1_, int i_) : CalcException("Syntax Error: Not allowed symbol character\n", file_, line_, func_, ("Symbol character found: '" + arg1_.substr(i_, 1))),
arg1(arg1_),
i(i_)
{
}

std::string CalcNotAllowedCharException::get_info() const
{
	return (info + "' at position " + std::to_string(i) + ". Symbol has been removed");
}

CalcFoundTypooException::CalcFoundTypooException(const char* file_, int line_, const char* func_, std::string arg1_, int i_) : CalcException("Syntax Error: Found symbol typoo.\n", file_, line_, func_, ("Two same symbol characters occured one after the other: '" + arg1_.substr(i_, 2))),
arg1(arg1_),
i(i_)
{
}

std::string CalcFoundTypooException::get_info() const
{
	return (info + "' at position " + std::to_string(i) + ". Doubled symbol has been removed");
}


CalcOperatorsSyntaxException::CalcOperatorsSyntaxException(const char* file_, int line_, const char* func_, std::string arg1_, int i_) : CalcException("Syntax Error: Illegal two operators next to each other.\n", file_, line_, func_, ("Two different Symbol characters found: '" + arg1_.substr(i_, 2))),
arg1(arg1_),
i(i_)
{
}

std::string CalcOperatorsSyntaxException::get_info() const
{
	return (info + "' at position " + std::to_string(i) + ". First symbol has been removed");
}


CalcMinusSyntaxException::CalcMinusSyntaxException(const char* file_, int line_, const char* func_, std::string arg1_, int i_) : CalcException("Syntax Error: Two minuses next to each other.\n", file_, line_, func_, ("2 minus operators found: '" + arg1_.substr(i_, 3))),
arg1(arg1_),
i(i_)
{
}

std::string CalcMinusSyntaxException::get_info() const
{
	return (info + "' at position " + std::to_string(i) + ". Two minuses changed to plus");
}

CalcBracketSyntaxException::CalcBracketSyntaxException(const char* file_, int line_, const char* func_, std::string arg1_, int i_, int bracketNum_) : CalcException("Syntax Error: Bracket mismatch.\n", file_, line_, func_, ("" + arg1_.substr(i_, 2))),
arg1(arg1_),
i(i_),
bracketNum(bracketNum_)
{
}

std::string CalcBracketSyntaxException::get_info() const
{
	if (bracketNum<0)
		return (info + "Found non opened bracket at position " + std::to_string(i) + ". Bracket has been removed");
	else
		return (info + "Found non closed bracket at position " + std::to_string(i) + ". Bracket has been added at the end of the string.");
}

ForceMultiply::ForceMultiply() : CalcException()
{
}
