/*
*******************************************
DO NOT TOUCH THIS FILE
*******************************************
*/
#ifndef CHECKINGACCOUNT_H_
#define CHECKINGACCOUNT_H_

#include "BankAccount.h"

class CheckingAccount: public BankAccount {
public:
	double getBalance(); //See definition of the function in the BankAccount.h
	void deposit(double amoutOfMoney); //See definition of the function in the BankAccount.h
	void withdraw(double amountOfMoney); //See definition of the function in the BankAccount.h
};

#endif

/*
*******************************************
DO NOT TOUCH THIS FILE
*******************************************
*/