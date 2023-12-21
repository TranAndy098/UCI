#include "CalculatorClass.hpp"
#include <iostream>
#include "ExceptionClass.cpp"

CalculatorClass::CalculatorClass()
{
    this->denominator = 0;
    this->numerator = 0;
}

int CalculatorClass::divideNumbers(int numerator,int denominator)
{
    int results = -1;
    std::string negativeNumberException = "One of the integers is negative";
    try {
        if (denominator == 0) {
            throw "Divide by Zero Exception Found!";
        }
        if (numerator < 0) {
            throw negativeNumberException;
        }
        else if (denominator < 0) {
            throw -100;
        }
        else if (denominator == 1000) {
            throw myCustomException();
        }
        else {
            results = numerator / denominator;
        }
    }
    catch (const char* msg){
        std::cout << "Char:Constant Divide by Exception Occured\n";
    }
    catch (std::string &msg){
            std::cout << "String:Constant Divide by Exception Occured\n";
    }
    catch (int num){
            std::cout << "Int:Constant Divide by Exception Occured\n";
    }
//    catch (std::exception &e){
//        std::cout << "I have a divide by zero excpetion\n";
//    }
    return results;
}
