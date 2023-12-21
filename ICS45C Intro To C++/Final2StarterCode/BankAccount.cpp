#include "BankAccount.h"

/*
**************************************************************
YOUR CODE STARTS HERE. DEFINE THE FUNCTIONS AS DESCRIBED IN THE
CORRESPONDING HEADER FILE. YOU MUST NOT ADD ANY INCLUDE
***************************************************************
*/


BankAccount::BankAccount(){
    this->firstName = "First";
    this->lastName = "Last";
    this->accountNumber = "0";
    totalAmountOfMoney = 0;
}
void BankAccount::setFirstName(std::string firstName){
    this->firstName = firstName;
}
std::string BankAccount::getFirstName(){
    return this->firstName;
}
void BankAccount::setLastName(std::string lastName){
    this->lastName = lastName;
}
std::string BankAccount::getLastName(){
    return this->lastName;
}
void BankAccount::setAccountNumber(std::string accountNumber){
    this->accountNumber = accountNumber;
}
std::string BankAccount::getAccountNumber() {
    return this->accountNumber;
}

/*
*******************************************
YOUR CODE ENDS HERE
*******************************************
*/
