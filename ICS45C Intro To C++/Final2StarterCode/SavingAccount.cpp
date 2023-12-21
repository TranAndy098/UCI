#include "SavingAccount.h"
#include <math.h>

/*
**************************************************************
YOUR CODE STARTS HERE. DEFINE THE FUNCTIONS AS DESCRIBED IN THE 
CORRESPONDING HEADER FILE. YOU MUST NOT ADD ANY INCLUDE
***************************************************************
*/

SavingAccount::SavingAccount(){
    this->amountOfSavingMoney = 0;
}

double SavingAccount::getBalance(){
    return totalAmountOfMoney + this->amountOfSavingMoney;
}

void SavingAccount::deposit(double amoutOfMoney){
    totalAmountOfMoney += amoutOfMoney;
}

void SavingAccount::withdraw(double amountOfMoney){
    if (amountOfMoney > totalAmountOfMoney) {
        throw TooMuchMoneyToWithdraw();
    }
    totalAmountOfMoney -= amountOfMoney;
}

void SavingAccount::setAmountOfSavingMoney(double amountOfSavingMoney){
    this->amountOfSavingMoney = amountOfSavingMoney;
}

double SavingAccount::getAmountOfSavingMoney(){
    return this->amountOfSavingMoney;
}

void SavingAccount::depositIntoSavingMoney(double amountOfMoney){
    this->amountOfSavingMoney += amountOfMoney;
}

void SavingAccount::withdrawFromSavingMoney(double amountOfMoney){
    if (amountOfMoney > this->amountOfSavingMoney) {
        throw TooMuchMoneyToWithdraw();
    }
    this->amountOfSavingMoney -= amountOfMoney;
}

double SavingAccount::getAmountOfSavingMoneyWithInterest(int t) {
    double ir = 0;
    ir = 1 + (r/n);
    ir = pow(ir, (n*t));
    return this->amountOfSavingMoney * ir;
}

/*
*******************************************
YOUR CODE ENDS HERE
*******************************************
*/
