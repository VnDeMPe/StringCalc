// StringCalc.cpp : This file contains the 'main' function. Program execution begins and ends there.

//Main program 

//To do
//Add user interface - new class? 

#include "Arithmetic.h"
#include "ArithProc.h"
#include "ArithDebug.h"
#include <iostream>

void intro()
{
    std::cout << "String Calculator" << std::endl;
    std::cout << "Instructions:\n '+' for addition\n '-' for substraction\n '*' for multiplication\n '/' for division\n '^' for exponentiation (example: 2^5 will return 32)\n '$' for square rooting (example: 32$5 will return 2)" << std::endl;
    std::string testStr = " (2 + 3) * ((4+ 5+ 6)*2) * 3 -128$7";
    std::cout << "example input: " << testStr<<std::endl;
    ArithProc::CalculateIt(testStr);
}

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
    ArithProc::CalculateIt(inputString);
    std::cout << "\nDo you want to try again? (type 'y' for yes): ";
    std::cin >> tryAgain;
    }     
    while (tryAgain == 'y');
    
}

