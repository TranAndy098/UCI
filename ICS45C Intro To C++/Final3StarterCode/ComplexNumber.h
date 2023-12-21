/*
*******************************************
DO NOT TOUCH THIS FILE
*******************************************
*/
#ifndef COMPLEXNUMBER_H_
#define COMPLEXNUMBER_H_

#include <iostream>

class ComplexNumber {
private:
	int realPart;
	int imaginaryPart;
public:
	ComplexNumber(); //Default constructor (Initialize your class variables with default values for variables)
	ComplexNumber(int realPart, int imaginaryPart); //A constructor that takes two integers and set them equal to the private members (realPart and imaginaryPart)
	void setRealPart(int realPart); //Setter for the realPart of the complex number.
	int getRealPart(); //Getter for the realPart of the complex number.
	void setImaginaryPart(int imaginaryPart); //Setter for the imaginaryPart of the complex number.
	int getImaginaryPart(); //Getter for the imaginaryPart of the complex number.
	
	/*When adding two complex numbers, the realPart of the first one gets added to the realPart of the second one. The same goes for the imaginaryPart 
	(1 + 2i)+(2 + 4i) = 3 + 6i. Remember you have already one of the complex numbers passed through the operator, the other one is your class that you are in 
	and you must RETURN the result.*/
	ComplexNumber operator+(const ComplexNumber& secondNumber);

	/*When subtracting two complex numbers, the realPart of the second one gets subtracted from the realPart of the first one (normal subtraction). The same 
	goes for the imaginaryPart (1 + 2i)-(2 + 4i) = -1 - 2i. Remember you have already one of the complex numbers passed through the operator, the other one is your 
	class that you are in and you must RETURN the result.*/
	ComplexNumber operator-(const ComplexNumber& secondNumber);

	/*When multiplying two complex numbers, you must distribute them. For example, (1+2i)*(2+4i) = 1*2 + 1*4i + 2i*2 + 2i*4i = 2 + 4i + 4i + 8i^2 but because i^2 = -1 
	then the result becomes 2 + 4i + 4i + 8(-1) = 2 + 4i + 4i - 8 = -6 + 8i. Remember you have already one of the complex number passed through the operator, the other 
	one is your class that you are in and you must RETURN the result.
	*/
	ComplexNumber operator*(const ComplexNumber& secondNumber); 

	friend std::ostream& operator<<(std::ostream& os, const ComplexNumber& cn); //Already done for you in ComplexNumber.cpp
};

#endif

/*
*******************************************
DO NOT TOUCH THIS FILE
*******************************************
*/