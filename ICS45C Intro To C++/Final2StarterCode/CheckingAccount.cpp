#include "CheckingAccount.h"

/*
**************************************************************
YOUR CODE STARTS HERE. DEFINE THE FUNCTIONS AS DESCRIBED IN THE
CORRESPONDING HEADER FILE. YOU MUST NOT ADD ANY INCLUDE
***************************************************************
*/


double CheckingAccount::getBalance(){
    return totalAmountOfMoney;
}

void CheckingAccount::deposit(double amoutOfMoney){
    totalAmountOfMoney += amoutOfMoney;
}

void CheckingAccount::withdraw(double amountOfMoney) {
    if (amountOfMoney > totalAmountOfMoney) {
        throw TooMuchMoneyToWithdraw();
    }
    totalAmountOfMoney -= amountOfMoney;
}

/*
*******************************************
YOUR CODE ENDS HERE
*******************************************
*/
