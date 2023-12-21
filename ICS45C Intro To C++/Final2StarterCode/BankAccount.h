/*
*******************************************
DO NOT TOUCH THIS FILE
*******************************************
*/

#ifndef BANKACCOUNT_H_
#define BANKACCOUNT_H_

#include <string>
#include <exception>

class TooMuchMoneyToWithdraw : public std::exception {
public:
    const char* what() const throw() {
	return "Too Much Money To Withdraw"; }
};

class BankAccount {
private:
	std::string firstName;
	std::string lastName;
	std::string accountNumber;
protected:
	double totalAmountOfMoney;
public:
	BankAccount(); //Default constructor (Initialize your class variables with default values for variables)
	void setFirstName(std::string firstName); //Setter for the firstName of the bank account
	std::string getFirstName(); //Getter for the firstName of the bank account
	void setLastName(std::string lastName); //Setter for the lastName of the bank account
	std::string getLastName(); //Getter for the lastName of the bank account
	void setAccountNumber(std::string accountNumber); //Setter for the accountNumber of the bank account
	std::string getAccountNumber(); //Getter for the accountNumber of the bank account

	/*The following are three pure virtual functions, notice we are setting the functions to 0. THEY DO NOT GET DEFINED IN THE BASE CLASS
	(this class - BankAccount.h/BankAccount.cpp). They will be defined in the derived classes that are inheriting from the BankAccount class.*/

	/*Pure virtual function that returns the current balance in the account.*/
	virtual double getBalance() = 0;
	/*Pure virtual function to deposit money in the account.*/
	virtual void deposit(double amoutOfMoney) = 0;
	/*Pure virtual function to withdraw money from the account, might throw TooMuchMoneyToWithdrawn exception.*/
	virtual void withdraw(double amountOfMoney) = 0;
};

#endif

/*
*******************************************
DO NOT TOUCH THIS FILE
*******************************************
*/
