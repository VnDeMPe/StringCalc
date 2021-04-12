#include "CalcException.h"
#include <iostream>




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

CalcFoundTypooException::CalcFoundTypooException(const char* file_, int line_, const char* func_, std::string arg1_, int i_) : CalcException("Syntax Error: Found typoo Symbol.\n", file_, line_, func_, ("Double Symbol character found: '" + arg1_.substr(i_, 1))),
arg1(arg1_),
i(i_)
{
}

std::string CalcFoundTypooException::get_info() const
{
	return (info + "' at position " + std::to_string(i) + ". Second ymbol has been removed");
}