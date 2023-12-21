#include "Renter.h"

Renter::Renter(){
    this->renterID = 0000;
    this->renterFirstName = "First";
    this->renterLastName = "Last";
}

Renter::Renter(int renterID, std::string renterFirstName, std::string renterLastName){
    this->renterID = renterID;
    this->renterFirstName = renterFirstName;
    this->renterLastName = renterLastName;
}

void Renter::setRenterID(int renterID){
    this->renterID = renterID;
}

int Renter::getRenterID(){
    return this->renterID;
}

void Renter::setRenterFirstName(std::string renterFirstName){
    this->renterFirstName = renterFirstName;
}

std::string Renter::getRenterFirstName(){
    return this->renterFirstName;
}

void Renter::setRenterLastName(std::string renterLastName){
    this->renterLastName = renterLastName;
}

std::string Renter::getRenterLastName(){
    return this->renterLastName;
}
