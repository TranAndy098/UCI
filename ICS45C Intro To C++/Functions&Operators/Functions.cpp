#include <iostream>

// Define a fucntion that performs a number swap
void numberSwap(int numberOne, int numberTwo) {
    int tempNumber = numberOne; // sets my temp variable to reatin the original value of numberOne
    numberOne = numberTwo; // sets numberOne to the original value of numberTwo
    numberTwo = tempNumber; // sets numberTwo to the original value of numberOne
    std::cout << "Within numberSwap (ints): " << numberOne << ", " << numberTwo << std::endl;
}

// we can have a funciton witht he same name but it needs to have soemthing that is different like a parameter type or order so the ide knows which to use
void numberSwap(double numberOne, int numberTwo) {
    int tempNumber = numberOne; // sets my temp variable to reatin the original value of numberOne
    numberOne = numberTwo; // sets numberOne to the original value of numberTwo
    numberTwo = tempNumber; // sets numberTwo to the original value of numberOne
    std::cout << "Within numberSwap (double): " << numberOne << ", " << numberTwo << std::endl;
}

void numberSwap(int numberOne, double numberTwo) {
    int tempNumber = numberOne; // sets my temp variable to reatin the original value of numberOne
    numberOne = numberTwo; // sets numberOne to the original value of numberTwo
    numberTwo = tempNumber; // sets numberTwo to the original value of numberOne
    std::cout << "Within numberSwap (double): " << numberOne << ", " << numberTwo << std::endl;
}
/*
// since this still matches the numberSwap(double numberOne, int numberTwo) with the only change the optional thrid paramter the ide will still not know what to use
void numberSwap(double numberOne, int numberTwo, int tempInt = 0) {
    int tempNumber = numberOne; // sets my temp variable to reatin the original value of numberOne
    numberOne = numberTwo; // sets numberOne to the original value of numberTwo
    numberTwo = tempNumber; // sets numberTwo to the original value of numberOne
    std::cout << "Within numberSwap (double): " << numberOne << ", " << numberTwo << std::endl;
}
*/
// by passing in a reference it will actually swap the values becasue it swaps the memory location and not a copy
void numberSwapRef(int &numberOne, int &numberTwo) {
    int tempNumber = numberOne; // sets my temp variable to reatin the original value of numberOne
    numberOne = numberTwo; // sets numberOne to the original value of numberTwo
    numberTwo = tempNumber; // sets numberTwo to the original value of numberOne
    std::cout << "Within numberSwap by Reference: " << numberOne << ", " << numberTwo << std::endl;
}

int main(int argc, const char * argv[]) {
    
    int mainOne = 10;
    int mainTwo = 20;
    double mainOneD = 15.5;
    
    numberSwap(mainOne, mainTwo);
    
    std::cout << "Outside numberSwap (ints): " << mainOne << ", " << mainTwo << std::endl;
    
    numberSwapRef(mainOne, mainTwo);
    
    std::cout << "Outside numberSwap by Reference: " << mainOne << ", " << mainTwo << std::endl;
    
    numberSwap(mainOneD, mainTwo);
    
    std::cout << "Outside numberSwap (double): " << mainOneD << ", " << mainTwo << std::endl;
    
    
    
    return 0;
}
