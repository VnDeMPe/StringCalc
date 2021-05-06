#pragma once
#ifndef CALCEXCEPTION_H_
#define CALCEXCEPTION_H_

#include "BaseCalc.h"
#include <string>
#include <exception>
#include <stdexcept>

class CalcException : public std::runtime_error, public BaseCalc {

protected:
    const char* _file;
    int _line;
    const char* _func;
    std::string _info;

public:
    CalcException(const char* msg, const char* file_, int line_, const char* func_, std::string info_);
    CalcException();
    static void LogException(CalcException &err);

    void DispException();

    const char* get_file() const;
    int get_line() const;
    const char* get_func() const;
    virtual std::string get_info() const;
};

class CalcZeroException : public CalcException  //Divide by zero exception, if divide by zero, divide by 1
{
private:
    double _arg1;
    double _arg2;
public:
    CalcZeroException(const char* file_, int line_, const char* func_, double arg1_, double arg2_);
    virtual std::string get_info() const override;
};

class CalcFirstDigitException : public CalcException   //First character in a string is not a digit
{
private:
    std::string _arg1;
public:
	CalcFirstDigitException(const char* file_, int line_, const char* func_, std::string arg1_);
    virtual std::string get_info() const override;
};


class CalcFoundAlphaException : public CalcException   // Found alphabet letter in a string
{
private:
    std::string _arg1;
    int _i; 
public:
    CalcFoundAlphaException(const char* file_, int line_, const char* func_, std::string arg1_, int i_);
    virtual std::string get_info() const override;
};


class CalcNotAllowedCharException : public CalcException   // Found not allowed character in a string
{
private:
    std::string _arg1;
    int _i;
public:
    CalcNotAllowedCharException(const char* file_, int line_, const char* func_, std::string arg1_, int i_);
    virtual std::string get_info() const override;
};

class CalcFoundTypooException : public CalcException   // Found same character sign doubled
{
private:
    std::string _arg1;
    int _i;
public:
    CalcFoundTypooException(const char* file_, int line_, const char* func_, std::string arg1_, int i_);
     virtual std::string get_info() const override;
};

class CalcOperatorsSyntaxException : public CalcException   // Found two operators next to each other (i.e. */)
{
private:
    std::string _arg1;
    int _i;
public:
    CalcOperatorsSyntaxException(const char* file_, int line_, const char* func_, std::string arg1_, int i_);
    virtual std::string get_info() const override;
};

class CalcMinusSyntaxException : public CalcException   // Found two minuses next to each other
{
private:
    std::string _arg1;
    int _i;
public:
    CalcMinusSyntaxException(const char* file_, int line_, const char* func_, std::string arg1_, int i_);
    virtual std::string get_info() const override;
};


class CalcBracketSyntaxException : public CalcException   // Found a bracket without a pair
{
private:
    std::string _arg1;
    int _i, _bracketNum;
public:
    CalcBracketSyntaxException(const char* file_, int line_, const char* func_, std::string arg1_, int i_, int bracketNum_);
    virtual std::string get_info() const override;
};

class ForceMultiply : public CalcException   // insert '*' betweren a digit and a bracket
{
private:
    bool _isOpenBracket;
public:
    ForceMultiply();
};


class CalcEmptyBracketsException : public CalcException   // Found two operators next to each other (i.e. */)
{
private:
    std::string _arg1;
    int _i;
public:
    CalcEmptyBracketsException(const char* file_, int line_, const char* func_, std::string arg1_, int i_);
    virtual std::string get_info() const override;
};

#endif // !CALCEXCEPTION_H_   CalcEmptyBracketsException