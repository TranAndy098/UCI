//============================================================================
// Name        : Exceptions.cpp
//============================================================================

#include <iostream>
#include <exception>
using namespace std;

//Defines a public exception that extends the exception class
class myCustomException:public exception{
};

int division( int a, int b){
		string myMsg = "Can't Divide by zero.";
		//try{
			if (b == 0)
			{
				throw myMsg;//throws it as a string
				throw "Can't Divide by zero."; //will throw it as a character array
			}
/*		}catch(string &msg){
			cout << "Divide by 0 exception." << endl;
		}catch(...){};

		b=1;*/
		return (a/b);
}

int main() {
	bool flag1 = true;
	try{
		cout << "Divide: " << division(1,0) << endl;

		if(flag1){
			throw myCustomException();
		}

	}
	catch(const char* &msg){//catches a throw that throws a char pointer
		cout << "Divide by 0 exception." << endl;
	}
	catch(myCustomException & e1){
		cout << "My custom exception 1. " << endl;
	}
	catch(...){
		cout << "... Catch All" << endl;
	}
/*	catch(exception &e){
		cout << "Exception: Can't divide by zero" << endl;
	}*/

	cout << "I am done with exceptions." << endl;

	return 0;
}
