#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include <vector>
#include <exception>
#include <typeinfo>
#include <iostream>

class WrongInput : public std::exception {
public:
    const char* what() const throw() {
	return "Wrong Input"; }
};

/*
*************************************************************************************************************************************
YOUR CODE GETS ADDED BELOW THIS COMMENT BLOCK
*************************************************************************************************************************************
You are to complete the calculator class to take in 2 vectors, the first vector contains the n numbers to use in your calculation and
the second vector contains n-1 operations you are to perform on the vector of numbers. The purpose of this calc function is to
take the first 2 numbers from vector 1 and use the first operation in vector 2 to calculate the result. Then you take the result and
the next number in vector 1 and calculate the new result using the next operation in vector 2. When ALL the numbers and operations in
vector 1 and vector 2 have been processed then calc function will RETURN the result.

EXAMPLE: vector 1 is (5,3,1,2) and vector 2 is (+,-, *) then you will calculate (((5+3)-1)*2).

A few additional notes:
1. Valid inputs are limited to ints and doubles, any other type should result in an exception (WrongInput which is defined above). The only type that we will test your exception with is character (only alphabetic ones).
2. The exception (WrongInput) should ONLY be THROWN in the function (calc), main WILL CATCH it as it is shown in your test data in main.cpp
3. The example vectors given above are just examples, our test vectors will have vectors that are larger and smaller.
4. The code within the class is incomplete, ensure your functions are properly defined in addition to the functionality within them.
5. You do not need to have more functions than what is provided. Any helper functions should only be used by the calc function should you define any.
6. Don't worry that you are defining everything in a header file. It is because we are creating template
*/
template <typename T>
class Calculator {
public:
	T calc(std::vector <T> numbers , std::vector <char> operations) //Remember your function is templated (I only added the name, you have to put the right parameters and return type)
	{
        T total;
        if (typeid(T) == typeid(char)) {
            throw WrongInput();
        }
        for (unsigned int i = 0; i < numbers.size(); i++) {
            if (i == 0) {
                total = numbers[i];
            } else {
                switch (operations[i-1]) {
                    case '+':
                        total = total + numbers[i];
                        break;
                    case '-':
                        total = total - numbers[i];
                        break;
                    case '*':
                        total = total * numbers[i];
                        break;
                    case '/':
                        total = total / numbers[i];
                        break;
                }
            }
            
        }
        return total;
        
	}
};

#endif

/*
*******************************************
YOUR CODE ENDS HERE
*******************************************
*/
