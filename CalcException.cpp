#include "CalcException.h"
#include <iostream>

//Handling Exception Classes 

void CalcException::LogException(CalcException &error)
{
	std::cout << error.what() << error.get_info() << std::endl;
	BaseCalc::AddToOutputLog(error.what());
	BaseCalc::AddToOutputLog(error.get_info());
}

const char* CalcException::get_file() const 
{
	return _file; 
}
int CalcException::get_line() const 
{ 
	return _line; 
}
const char* CalcException::get_func() const 
{ 
	return _func; 
}

std::string CalcException::get_info() const 
{ 
	return _info; 
}

void CalcException::DispException()
{
	std::cout <<"\nException occured in file " <<get_file() << " in Function: " << get_func() << " at line nr " <<get_line() << std::endl;
}

CalcException::CalcException(const char* msg, const char* file_, int line_, const char* func_, std::string info_ = "Errore") : std::runtime_error(msg),
_file(file_),
_line(line_),
_func(func_),
_info(info_)
{
	DispException();
}

CalcException::CalcException(const char* msg) : std::runtime_error(msg)
{
}


std::string CalcZeroException::get_info() const 
{ 
	return (_info + ": 0 has been changed to 1"); 
}


CalcZeroException::CalcZeroException(const char* file_, int line_, const char* func_, double arg1_, double arg2_) : CalcException("Math Error: Not allowed to divide by zero\n", file_, line_, func_, ("Attempt to divide " + std::to_string(arg1_) + " with " + std::to_string(arg2_)) ),
_arg1(arg1_),
_arg2(arg2_)
{
}

CalcFirstDigitException::CalcFirstDigitException(const char* file_, int line_, const char* func_, std::string arg1_) : CalcException("Syntax Error: Missing first digit\n", file_, line_, func_, ("No digit on the left side of operation: '" + arg1_.substr(0,2) )),
_arg1(arg1_)
{
}

std::string CalcFirstDigitException::get_info() const
{
	return (_info + "'. 0 added as first digit");
}

CalcFoundAlphaException::CalcFoundAlphaException(const char* file_, int line_, const char* func_, std::string arg1_, int i_) : CalcException("Syntax Error: Found alphabet letter\n", file_, line_, func_, ("Alphabet character found: '" + arg1_.substr(i_, 1))),
_arg1(arg1_),
_i(i_)
{
}

std::string CalcFoundAlphaException::get_info() const
{
	return (_info + "' at position " + std::to_string(_i) + ". Character has been removed");
}

CalcNotAllowedCharException::CalcNotAllowedCharException(const char* file_, int line_, const char* func_, std::string arg1_, int i_) : CalcException("Syntax Error: Not allowed symbol character\n", file_, line_, func_, ("Symbol character found: '" + arg1_.substr(i_, 1))),
_arg1(arg1_),
_i(i_)
{
}

std::string CalcNotAllowedCharException::get_info() const
{
	return (_info + "' at position " + std::to_string(_i) + ". Symbol has been removed");
}

CalcFoundTypooException::CalcFoundTypooException(const char* file_, int line_, const char* func_, std::string arg1_, int i_) : CalcException("Syntax Error: Found symbol typoo.\n", file_, line_, func_, ("Two same symbol characters occured one after the other: '" + arg1_.substr(i_, 2))),
_arg1(arg1_),
_i(i_)
{
}

std::string CalcFoundTypooException::get_info() const
{
	return (_info + "' at position " + std::to_string(_i) + ". Doubled symbol has been removed");
}


CalcOperatorsSyntaxException::CalcOperatorsSyntaxException(const char* file_, int line_, const char* func_, std::string arg1_, int i_) : CalcException("Syntax Error: Illegal two operators next to each other.\n", file_, line_, func_, ("Two different Symbol characters found: '" + arg1_.substr(i_, 2))),
_arg1(arg1_),
_i(i_)
{
}

std::string CalcOperatorsSyntaxException::get_info() const
{
	return (_info + "' at position " + std::to_string(_i) + ". One symbol has been removed");
}


CalcMinusSyntaxException::CalcMinusSyntaxException(const char* file_, int line_, const char* func_, std::string arg1_, int i_) : CalcException("Syntax Error: Two minuses next to each other.\n", file_, line_, func_, ("2 minus operators found: '" + arg1_.substr(i_, 3))),
_arg1(arg1_),
_i(i_)
{
}

std::string CalcMinusSyntaxException::get_info() const
{
	return (_info + "' at position " + std::to_string(_i) + ". Two minuses changed to plus");
}

CalcBracketSyntaxException::CalcBracketSyntaxException(const char* file_, int line_, const char* func_, std::string arg1_, int i_, int bracketNum_) : CalcException("Syntax Error: Bracket mismatch.\n", file_, line_, func_, ("" + arg1_.substr(i_, 2))),
_arg1(arg1_),
_i(i_),
_bracketNum(bracketNum_)
{
}

std::string CalcBracketSyntaxException::get_info() const
{
	if (_bracketNum<0)
		return (_info + "Found non opened bracket at position " + std::to_string(_i) + ". Bracket has been removed");
	else
		return (_info + "Found non closed bracket at position " + std::to_string(_i) + ". Bracket has been added at the end of the string.");
}

ForceMultiply::ForceMultiply() : CalcException("")
{
}


CalcEmptyBracketsException::CalcEmptyBracketsException(const char* file_, int line_, const char* func_, std::string arg1_, int i_) : CalcException("Syntax Error: Found empty pair of brackets.\n", file_, line_, func_, ("Empty brackets inside of the string found '" + arg1_.substr(i_, 2))),
_arg1(arg1_),
_i(i_)
{
}

std::string CalcEmptyBracketsException::get_info() const
{
	return (_info + "' at position " + std::to_string(_i) + ". Brackets has been removed");
}



