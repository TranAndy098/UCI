/*
*******************************************
DO NOT TOUCH THIS FILE
*******************************************
*/

#ifndef SAVINGACCOUNT_H_
#define SAVINGACCOUNT_H_

#include "BankAccount.h"

class SavingAccount: public BankAccount {
private:
	double r = 0.05;
	int n = 12;
	double amountOfSavingMoney;
public:
	SavingAccount(); //Default constructor (Initialize your class variables with default values for variables which are not already initialized)
	double getBalance(); //See definition of the function in the BankAccount.h
	void deposit(double amoutOfMoney); //See definition of the function in the BankAccount.h
	void withdraw(double amountOfMoney); //See definition of the function in the BankAccount.h
	void setAmountOfSavingMoney(double amountOfSavingMoney); //Setter for the amountOfSavingMoney of the saving account
	double getAmountOfSavingMoney(); //Getter for the amountOfSavingMoney of the saving account
	
	/*This function will only deposit money into your savings account amountOfSavingMoney, not the amount inherited from the BankAccount base class.*/
	void depositIntoSavingMoney(double amountOfMoney); 
	
	/* This function will only withdraw money from your savings account amountOfSavingMoney, not the amount inherited from the BankAccount base class. 
	It also will throw TooMuchMoneyToWithdraw exception if you do not have enough money in amountOfSavingMoney.*/
	void withdrawFromSavingMoney(double amountOfMoney); 
	
	/* This function is an interest calculator which will return the estimated interest accrued based on the amount of money currently
	in the savings using the formula P*(1 + r/n)^(nt), where P is how much you have in the saving portion of your account, t is number of 
	years you want to calculate for, n and r are giving constant values. For rounding, you either round the number up to two digits after 
	the decimal or you can keep it as is. For example, 11.116 will work if you keep it like that or make it 11.12 or 11.11
	*/
	double getAmountOfSavingMoneyWithInterest(int t);
};

#endif

/*
*******************************************
DO NOT TOUCH THIS FILE
*******************************************
*/