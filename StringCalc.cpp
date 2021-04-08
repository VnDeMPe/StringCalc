// StringCalc.cpp : This file contains the 'main' function. Program execution begins and ends there.

//Main program 

//To do
//Add user interface - new class? 

#include <iostream>
#include "Arithmetic.h"
#include "ArithProc.h"
//#include "ArithDebug.h"


int main()
{   
    std::cout << "String Calculator" << std::endl;
    std::cout << "Instructions:\n '+' for addition\n '-' for substraction\n '*' for multiplication\n '/' for division\n '^' for exponentiation (example: 2^5 will return 32)\n '$' for square rooting (example: 32$5 will return 2)" << std::endl;
    std::string testStr = " (2 + 3) * ((4+ 5+ 6)*2) * 3 -128$7";
    std::cout << "example input: " << testStr;
    ArithProc::CalculateIt(testStr);
    std::string inputString;
    std::cout << "Enter the data: ";
    std::getline(std::cin, inputString);
    std::cout << inputString << std::endl;
    ArithProc::CalculateIt(inputString);
}

