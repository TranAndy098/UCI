#ifndef MOVIEMANAGERUI_H_
#define MOVIEMANAGERUI_H_

#include <string>

class MovieManagerUI{
private:
	std::string toUpper(std::string);
public:
	void printMenu();
	std::string getCommand();
	std::string getMovieName();
	std::string getMovieCode();
	int getRenterID();
	std::string getRenterFirstName();
	std::string getRenterLastName();
	void invalidSelection();
	void enterToContinue();
	void print(std::string);
};

#endif
