#pragma once
#ifndef CALCEXCEPTION_H_
#define CALCEXCEPTION_H_

#include <string>
#include <exception>
#include <stdexcept>

class CalcException : public std::runtime_error {

protected:
    const char* file;
    int line;
    const char* func;
    std::string info;

public:
    CalcException(const char* msg, const char* file_, int line_, const char* func_, std::string info_);
    CalcException();
    void DispException();

    const char* get_file() const;
    int get_line() const;
    const char* get_func() const;
    virtual std::string get_info() const;

};

class CalcZeroException : public CalcException  //Divide by zero exception, if divide by zero, divide by 1
{
private:
    double arg1;
    double arg2;
public:
    CalcZeroException(const char* file_, int line_, const char* func_, double arg1_, double arg2_);
    virtual std::string get_info() const override;
};

class CalcFirstDigitException : public CalcException   //First character in a string is not a digit
{
private:
    std::string arg1;
public:
	CalcFirstDigitException(const char* file_, int line_, const char* func_, std::string arg1_);
    virtual std::string get_info() const override;
};


class CalcFoundAlphaException : public CalcException   // Found alphabet letter in a string
{
private:
    std::string arg1;
    int i; 
public:
    CalcFoundAlphaException(const char* file_, int line_, const char* func_, std::string arg1_, int i_);
    virtual std::string get_info() const override;
};


class CalcNotAllowedCharException : public CalcException   // Found alphabet letter in a string
{
private:
    std::string arg1;
    int i;
public:
    CalcNotAllowedCharException(const char* file_, int line_, const char* func_, std::string arg1_, int i_);
    virtual std::string get_info() const override;
};

class CalcFoundTypooException : public CalcException   // Found alphabet letter in a string
{
private:
    std::string arg1;
    int i;
public:
    CalcFoundTypooException(const char* file_, int line_, const char* func_, std::string arg1_, int i_);
    virtual std::string get_info() const override;
};

class CalcOperatorsSyntaxException : public CalcException   // Found alphabet letter in a string
{
private:
    std::string arg1;
    int i;
public:
    CalcOperatorsSyntaxException(const char* file_, int line_, const char* func_, std::string arg1_, int i_);
    virtual std::string get_info() const override;
};

class CalcMinusSyntaxException : public CalcException   // Found alphabet letter in a string
{
private:
    std::string arg1;
    int i;
public:
    CalcMinusSyntaxException(const char* file_, int line_, const char* func_, std::string arg1_, int i_);
    virtual std::string get_info() const override;
};


class CalcBracketSyntaxException : public CalcException   // Found alphabet letter in a string
{
private:
    std::string arg1;
    int i, bracketNum;
public:
    CalcBracketSyntaxException(const char* file_, int line_, const char* func_, std::string arg1_, int i_, int bracketNum_);
    virtual std::string get_info() const override;
};

class ForceMultiply : public CalcException   // insert '*' betweren a digit and a bracket
{
private:
    bool IsOpenBracket;
public:
    ForceMultiply();
};

#endif // !CALCEXCEPTION_H_