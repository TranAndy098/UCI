#include <iostream>
#include "CalculatorClass.hpp"
#include "ExceptionClass.cpp"

int main() {
    CalculatorClass myCalc;
    int myFlag = 0;
    try {
        std::cout << "10 divided by 5 is " << myCalc.divideNumbers(10,5) << std::endl;
        std::cout << "10 divided by 0 is " << myCalc.divideNumbers(10,0) << std::endl;
        std::cout << "10 divided by -10 is " << myCalc.divideNumbers(10,-10) << std::endl;
        std::cout << "-10 divided by -10 is " << myCalc.divideNumbers(-10,-10) << std::endl;
        std::cout << "10 divided by 1000 is " << myCalc.divideNumbers(10,1000) << std::endl;
        if (myFlag == 0) {
            throw myCustomException2();
        }
        else if (myFlag == 1) {
            std::cout << "-10 divided by -10 is " << myCalc.divideNumbers(-10,-10) << std::endl;
        }
        else {
            throw 10;
        }
    }
    catch (myCustomException& e){
        std::cout << "I caught my own exception\n";
    }
    catch (std::exception &e){
        std::cout << "I caught other exception\n";
    }
    catch (...){
        std::cout << "catch everything including all other exceptions\n";
    }
        return 0;
}
