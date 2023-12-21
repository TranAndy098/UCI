#include "ComplexNumber.h"

/*
**************************************************************
YOUR CODE STARTS HERE. DEFINE THE FUNCTIONS AS DESCRIBED IN THE
CORRESPONDING HEADER FILE. YOU MUST NOT ADD ANY INCLUDE
***************************************************************
*/

ComplexNumber::ComplexNumber(){
    this->realPart = 0;
    this->imaginaryPart = 0;
}
ComplexNumber::ComplexNumber(int realPart, int imaginaryPart){
    this->realPart = realPart;
    this->imaginaryPart = imaginaryPart;
}
void ComplexNumber::setRealPart(int realPart){
    this->realPart = realPart;
}
int ComplexNumber::getRealPart(){
    return this->realPart;
}
void ComplexNumber::setImaginaryPart(int imaginaryPart){
    this->imaginaryPart = imaginaryPart;
}
int ComplexNumber::getImaginaryPart(){
    return this->imaginaryPart;
}
ComplexNumber ComplexNumber::operator+(const ComplexNumber& secondNumber){
    ComplexNumber cn;
    cn.realPart = (this->realPart + secondNumber.realPart);
    cn.imaginaryPart = (this->imaginaryPart + secondNumber.imaginaryPart);
    return cn;
    
}
ComplexNumber ComplexNumber::operator-(const ComplexNumber& secondNumber){
    ComplexNumber cn;
    cn.realPart = (this->realPart - secondNumber.realPart);
    cn.imaginaryPart = (this->imaginaryPart - secondNumber.imaginaryPart);
    return cn;
}

ComplexNumber ComplexNumber::operator*(const ComplexNumber& secondNumber) {
    ComplexNumber cn;
    cn.realPart = (this->realPart * secondNumber.realPart) - (this->imaginaryPart * secondNumber.imaginaryPart);
    cn.imaginaryPart = (this->realPart * secondNumber.imaginaryPart) + (this->imaginaryPart * secondNumber.realPart);
    return cn;
}

std::ostream& operator<<(std::ostream& os, const ComplexNumber& cn)
{
	os << "The complex number is: ";
	if (cn.imaginaryPart > -1)
	{
		os << cn.realPart << "+" << cn.imaginaryPart << "i" << std::endl;
	}
	else
	{
		os << cn.realPart << cn.imaginaryPart << "i" << std::endl;
	}
	return os;
}

/*
*******************************************
YOUR CODE ENDS HERE
*******************************************
*/
