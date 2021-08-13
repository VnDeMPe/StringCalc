// StringCalc.cpp : This file contains the 'main' function. Program execution begins and ends there.

//Main program W

#include "BaseCalc.h"
#include "Arithmetic.h"
#include "DataProcessing.h"
#include "ArithDebug.h"
#include "StringInit.h"
#include <iostream>
#include <objbase.h>


///
/// STATIC VARIABLES INITIALIZATION 
/// 
std::vector<std::string> BaseCalc::_outputLogs;
std::vector<double> BaseCalc::_arrayOfValues;
std::vector<char> BaseCalc::_arrayOfOperators;
std::vector<int> BaseCalc::_operatorPositionLvl1;
std::vector<int> BaseCalc::_operatorPositionLvl2;
std::vector<int> BaseCalc::_operatorPositionLvl3;

/// 
/// BASE CLASS METHODS DEFINITION
///
void BaseCalc::AddToOutputLog (std::string Log)
{
    _outputLogs.push_back(Log);
}
std::vector<std::string> BaseCalc::GetOutputLog()
{
    return _outputLogs;
}
void BaseCalc::ClearOutputLog()
{
    _outputLogs.clear();
}

///
/// MARSHAL FUNCTION DEFINITION
/// 
double  MarshalStringCalc(const char* pInputString, void (*addToList)(const char* pOutputString),int numFinDigital)
{
    BaseCalc::ClearOutputLog();

    std::string preparedString;
    double result = DataProcessing::CalculateIt(pInputString, preparedString, numFinDigital);

    addToList(preparedString.data());

    std::vector<std::string> loglist = BaseCalc::GetOutputLog();
    for (auto it = loglist.begin(); it != loglist.end(); ++it)   //for (auto& it : loglist)
    {
        addToList(it->data());
    }
    return result;
}

void intro()
{
    std::cout << "String Calculator" << std::endl;
    std::cout << "Instructions:\n '+' for addition\n '-' for substraction\n '*' for multiplication\n '/' for division\n '^' for exponentiation (example: 2^5 will return 32)\n '$' for square rooting (example: 32$5 will return 2)\n" << std::endl;
    std::string testStr = " ((2 + 3) * ((4+ 5+ 6)*2) * 3 -128$7)";
    std::cout << "example input: " << testStr<<std::endl;
    //DataProcessing::CalculateIt(testStr);
}

///
/// MAIN
///


int main()
{   
    ArithDebug::SetDebugMode(false);
    intro();

    char tryAgain;
    do
    {                                          
    std::string inputString;
    std::cout << "Enter the data: ";
    std::getline(std::cin >>std::ws, inputString);
    std::cout << inputString << std::endl;
    //DataProcessing::CalculateIt(inputString);
    std::cout << "\nDo you want to calculate a new string? (type 'y' for yes): ";
    std::cin >> tryAgain;
    }     
    while (tryAgain == 'y');
    
}

