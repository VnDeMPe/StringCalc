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
    int value = Arithmetic::Add(5, 4);
    std::cout << value << std::endl;
    value = Arithmetic::Multiply(4, 2);
    std::cout << value;
    std::string str = ".4 * 2 + 30.2 * 2";
    std::cout << str << std::endl;
    str.erase(remove_if(str.begin(), str.end(), isspace), str.end()); // without erase: n - number of erased spaces, will be additional n last chars before erase. f.e 1 + 2 + 3 will be 1+2+3' + 3' because 4 spaces removed
    std::cout << str << std::endl;
    std::string testStr2 = " 2.5 + 3.5 * 4.5+ 5.9+ 6.23 * 7.1";
    testStr2 = ArithProc::RemoveSpaces(testStr2);
    std::cout << testStr2 << std::endl;
    ArithProc::ScanString(testStr2);
    ArithDebug::DebugDisplayValues();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
