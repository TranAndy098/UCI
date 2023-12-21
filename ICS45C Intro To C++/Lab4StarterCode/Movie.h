#ifndef MOVIE_H_
#define MOVIE_H_

#include "Renter.h"
#include "CustomException.h"
#include <vector>

class Movie{
private:
	std::string movieCode;
	std::string movieName;
public:
	std::vector<Renter> renters;
	Movie();
	Movie(std::string, std::string);
	void setMovieCode(std::string);
	std::string getMovieCode();
	void setMovieName(std::string);
	std::string getMovieName();
	void rentMovie(Renter);
	void returnRental(int);
	bool isBeingRented();
	void printMovieInfo();
};
#endif
