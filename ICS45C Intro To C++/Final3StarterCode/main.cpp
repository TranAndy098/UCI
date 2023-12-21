#include "ComplexNumber.h"

void testing();

/*
******************************************************************************
DO NOT CHANGE ANYTHING IN MAIN
******************************************************************************
*/

int main()
{
	std::cout << "Start Testing" << std::endl;
	testing();
	std::cout << "Finish Testing" << std::endl;
	return 0;
}

/*
******************************************************************************
THESE ARE JUST A SUBSET OF THE TEST CASES ON GRADESCOPE
IF YOUR CODE COMPILES AND GIVES THE CORRECT RESULT ON THESE TEST CASES, IT 
DOES NOT MEAN THAT YOUR CODE IS 100% CORRECT AND IT IS NOT A GUARATNEE THAT
YOU WILL PASS ALL OF THE TEST CASES ON GRADESCOPE
WE PROVIDED THESE TEST CASES JUST TO SHOW YOU HOW WE WILL BE TESTING YOUR CODE
YOU (OPTINALLY) SHOULD ADD YOUR OWN TEST CASES
******************************************************************************
*/

void testing()
{
	ComplexNumber num1(1, 2);
	ComplexNumber num2(2, 4);
	ComplexNumber num3;
	ComplexNumber num4;
	ComplexNumber num5;
	num3 = num1 + num2;
	num4 = num1 - num2;
	num5 = num1 * num2;
	std::cout << num3;
	std::cout << "The complex number SHOULD BE: 3+6i" << std::endl;
	std::cout << num4;
	std::cout << "The complex number SHOULD BE: -1-2i" << std::endl;
	std::cout << num5;
	std::cout << "The complex number SHOULD BE: -6+8i" << std::endl;
}