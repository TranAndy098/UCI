#include "Calculator.h"
#include <iostream>

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
	try
	{
		Calculator<int> c1;
		std::vector<int> numbers1;
		numbers1.push_back(1);
		numbers1.push_back(2);
		numbers1.push_back(3);
		std::vector<char> operations1;
		operations1.push_back('+');
		operations1.push_back('*');
		std::cout << "YOUR RESULT: " << c1.calc(numbers1, operations1) << std::endl;
		std::cout << "EXPECTED RESULT: 9" << std::endl;
		std::cout << std::endl;
	}
	catch(WrongInput& e){
		std::cout << e.what() << std::endl;
	}

	try
	{
		Calculator<double> c2;
		std::vector<double> numbers2;
		numbers2.push_back(3.5);
		numbers2.push_back(2.0);
		numbers2.push_back(2.0);
		std::vector<char> operations2;
		operations2.push_back('+');
		operations2.push_back('*');
		std::cout << "YOUR RESULT: " << c2.calc(numbers2, operations2) << std::endl;
		std::cout << "EXPECTED RESULT: 11 OR 11.00 (DOESN'T MATTER AS LONG AS YOU GET 11)" << std::endl;
		std::cout << std::endl;
	}
	catch (WrongInput& e) {
		std::cout << e.what() << std::endl;
	}

	try
	{
		Calculator<char> c3;
		std::vector<char> numbers3;
		numbers3.push_back('a');
		numbers3.push_back('b');
		numbers3.push_back('c');
		std::vector<char> operations3;
		operations3.push_back('+');
		operations3.push_back('*');
		std::cout << "YOUR RESULT: " << c3.calc(numbers3, operations3) << std::endl;
		std::cout << "EXPECTED RESULT: There is not any expected result because the exception should get triggered here" << std::endl;
		std::cout << std::endl;
	}
	catch (WrongInput& e) {
		std::cout << e.what() << std::endl;
	}
}
