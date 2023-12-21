#ifndef CARS_HPP_
#define CARS_HPP_

#include <string>

class Cars
{
private:
	std::string color;
	std::string make;
	std::string model;
	int tankSize;
	int maxDistance;

public:
	std::string getColor();
	std::string getMake();
	std::string getModel();
	int getTankSize();
	int getMaxDistance();
	void setColor(std::string);
	void setMake(std::string);
	void setModel(std::string);
	void setTankeSize(int);
	void setMaxDistance(int);
	Cars(); // Declared a default constructor to intialize a car object without default data
	Cars(Cars&); //Declared a copy constructor that takes an existing object as the source data
	Cars(std::string, std::string, std::string, int, int); //Declared a constructor that takes in initial value during construction
    friend std::ostream& operator<<(std::ostream& os, Cars &) ;
};

#endif // !CARS_HPP_
