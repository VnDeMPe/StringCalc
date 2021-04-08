// StringCalc.cpp : This file contains the 'main' function. Program execution begins and ends there.

//Main program 

//To do
//Clean main 
//Add user interface - new class? 

#include <iostream>
#include "Arithmetic.h"
#include "ArithProc.h"
#include "ArithDebug.h"


int main()
{
    std::string testStr2 = " 2.5 + 3.5 * (4.5+ 5.9+ 6.23)^3 * 7.1 -128$7";
    testStr2 = ArithProc::RemoveSpaces(testStr2);
    ArithProc::ScanString(testStr2);
    ArithDebug::DebugDisplayValues();
}
