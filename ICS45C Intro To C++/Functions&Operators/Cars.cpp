#include "Cars.hpp"

Cars::Cars() {
	this->color = "White";
	this->make = "Toyota";
	this->model = "Camry";
	this->tankSize = 16;
	this->maxDistance = 500;
}
Cars::Cars(Cars &originalCar) {
	this->color = originalCar.getColor();
	this->make = originalCar.getMake();
	this->model = originalCar.getModel();
	this->tankSize = originalCar.getTankSize();
	this->maxDistance = originalCar.getMaxDistance();
}
Cars::Cars(std::string color, std::string make, std::string model, int tankSize, int maxDistance) {
	this->color = color;
	this->make = make;
	this->model = model;
	this->tankSize = tankSize;
	this->maxDistance = maxDistance;
}
std::string Cars::getColor() {
	return this->color;
}
std::string Cars::getMake() {
	return this->make;
}
std::string Cars::getModel() {
	return this->model;
}
int Cars::getTankSize(){
	return this->tankSize;
}
int Cars::getMaxDistance() {
	return this->maxDistance;
}
void Cars::setColor(std::string color) {
	this->color = color;
}
void Cars::setMake(std::string make) {
	this->make = make;
}
void Cars::setModel(std::string model) {
	this->model = model;
}
void Cars::setTankeSize(int tankSize) {
	this->tankSize = tankSize;
}
void Cars::setMaxDistance(int maxDistance){
	this->maxDistance = maxDistance;
}

std::ostream& operator<<(std::ostream& os, Cars &myCar) {
    std::string carInformation = "";
    carInformation += "My first car is a ";
    carInformation += myCar.color;
    carInformation += " ";
    carInformation += myCar.make;
    carInformation += " ";
    carInformation += myCar.model;
    carInformation += " that can travel ";
    carInformation += std::to_string(myCar.maxDistance);
    carInformation += " miles using ";
    carInformation += std::to_string(myCar.tankSize);
    carInformation += " gallons of gas.";
    carInformation += "\n";
    os << carInformation;
    return os;
}
