#ifndef MOVIEMANAGER_H_
#define MOVIEMANAGER_H_

#include "MovieManagerUI.h"
#include "Movie.h"

class MovieManager{
private:
	MovieManagerUI mmUI;
public:
	std::vector<Movie> movies;
	void run();
	void addMovie(Movie);
	void discontinueMovie(std::string);
	void rentMovie(std::string, Renter);
	void returnRental(int, std::string);
	void printInventory();
};
#endif
