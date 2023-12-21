#ifndef RENTER_H_
#define RENTER_H_

#include <string>

class Renter{
private:
	int renterID;
	std::string renterFirstName;
	std::string renterLastName;
public:
	Renter();
	Renter(int, std::string, std::string);
	void setRenterID(int);
	int getRenterID();
	void setRenterFirstName(std::string);
	std::string getRenterFirstName();
	void setRenterLastName(std::string);
	std::string getRenterLastName();
};

#endif
