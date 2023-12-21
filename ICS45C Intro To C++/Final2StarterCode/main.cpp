#include "CheckingAccount.h"
#include "SavingAccount.h"
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
	CheckingAccount account1;
	account1.setFirstName("Bruce");
	account1.setLastName("Wayne");
	account1.setAccountNumber("02191963");
	account1.deposit(5000);
	account1.withdraw(250);
	std::cout << "The checking account holder name is: " << account1.getFirstName() << " " << account1.getLastName() << ", and the account number is: " << account1.getAccountNumber() << std::endl;
	std::cout << "The checking account holder name SHOULD BE: Bruce Wayne, and the account number SHOULD BE: 02191963" << std::endl;
	std::cout << "The balance in the checking account is: $" << account1.getBalance() << std::endl;
	std::cout << "The balance in the cheking account SHOULD BE: $4750" << std::endl;
	SavingAccount account2;
	account2.setFirstName("Clark");
	account2.setLastName("Kent");
	account2.setAccountNumber("04181977");
	account2.deposit(1000);
	account2.setAmountOfSavingMoney(205);
	account2.withdraw(500);
	account2.depositIntoSavingMoney(5);
	account2.withdrawFromSavingMoney(10);
	std::cout << "The saving account holder name is: " << account2.getFirstName() << " " << account2.getLastName() << ", and the account number is: " << account2.getAccountNumber() << std::endl;
	std::cout << "The saving account holder name SHOULD BE: Clark Kent, and the account number SHOULD BE: 04181977" << std::endl;
	std::cout << "The balance in the saving account is: $" << account2.getBalance() << std::endl;
	std::cout << "The balance in the saving account SHOULD BE: $700" << std::endl;
	std::cout << "The saving account holder has: $" << account2.getAmountOfSavingMoney() << " in the saving portion of his account" << std::endl;
	std::cout << "The saving account holder SHOULD HAVE: $200 in the saving portion of his account" << std::endl;
	std::cout << "The saving account holder has: $" << account2.getAmountOfSavingMoneyWithInterest(2) << " in the saving portion of his account after 2 years with intereset" << std::endl;
	std::cout << "The saving account holder SHOULD HAVE: $220.988 or $220.98 or $220.99 in the saving portion of his account after 2 years with intereset" << std::endl;
}