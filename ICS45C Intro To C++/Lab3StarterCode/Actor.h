#ifndef ACTOR_H_
#define ACTOR_H_

#include <string>
#include <iostream>

class Actor {
private:
	std::string firstName;
	std::string lastName;
	int birthYear;
public:
	Actor();
	Actor(std::string, std::string, int);
	void setFirstName(std::string);
	std::string getFirstName();
	void setLastName(std::string);
	std::string getLastName();
	void setBirthYear(int);
	int getBirthYear();
};

#endif /* ACTOR_H_ */