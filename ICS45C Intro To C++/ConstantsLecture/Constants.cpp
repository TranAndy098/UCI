#include <iostream>

int main() {
    const int seconds = 60;
    const std::string clock = "Digital clock";
    
    std::cout << seconds << std::endl;
    
    /* declared constant but initalized later fives an error
    const int hours;
    hours = 24;
    */
    
    // atempting to modify a const value results in an error
    //seconds = 1000;
    //std::cout << seconds << std::endl;
    
    // determine which native string functions are allowed constants
    std::cout << clock << std::endl; // acceptable because we are not changing clock
    std::cout << clock.length() << std::endl; // acceptable because we are not changing clock length
    std::string clockCopy = clock; // acceptable because I am making a copy of the constant value
    clockCopy.clear(); // acceptable because I am clearing the copy not the original
    //clock += "is broken. "; // not acceptable becasue I am attempting append to a cosntant string
    clockCopy += "is broken. "; // acceptable becasue I am modifying the copy
    //clock.clear(); // not acceptable because I am attempting to clear the constant string value
    
    std::cout << clock << " shows " << seconds << " seconds" << std::endl;
    
    //--------------------------------------------------
    
    // examples of how C++ prevents the potential for modifying a constant value
    const int hours = 24;
    const int minutes = hours;
    int days = hours;
    const int years = days;
    //int& refHours = hours; // not acceptable becasue this allows the user to modify the constant value through the reference
    //refHours = 100;
    //int* ptrHours = &hours; // not acceptable becasue this allows the user to modify the constant value through the pointer
    //*ptrHours = 200;
    
    std::cout << "Years: " << years << std::endl;
    days = 365;
    std::cout << "Years: " << years << std::endl;
    
    // constant references
    int someInt = 4;
    const int& someRefInt = someInt;
    //someRefInt = 20; // not accepetalbe because since the reference is the constant we can not change it
    
    std::cout << "someRefInt before: " << someRefInt << std::endl;
    std::cout << "someInt before: " << someInt << std::endl;
    someInt = 10;
    std::cout << "someRefInt after: " << someRefInt << std::endl;
    std::cout << "someInt after: " << someInt << std::endl;
    
    // constant pointers examples
    int *planPtr;
    int anotherInt = 250;
    const int* constPtr = &someInt;
    someInt = 100;
    //*constPtr = 200; // not acceptable because having the constant pointer means the pointer can not be modified
    int const* anotherConstPtr = &someInt;
    //*anotherConstPtr = 400; // not acceptable because having the constant pointer means the pointer can not be modified
    int * const constPtr2 = &someInt;
    *constPtr2 = 500;
    //constPtr2 = &anotherInt; // can not reassign the variable I am pointing constPtr2
    
    std::cout << "Pointing to someInt: " << constPtr << std::endl;
    std::cout << "Pointing to someInt: " << anotherConstPtr << std::endl;
    
    return 0;
}

