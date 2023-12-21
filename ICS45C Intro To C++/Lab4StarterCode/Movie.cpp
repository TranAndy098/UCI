#include "Movie.h"
#include <iostream>

Movie::Movie(){
    this->movieCode = "MovieCode";
    this->movieName = "MovieName";
}

Movie::Movie(std::string movieCode, std::string movieName){
    this->movieCode = movieCode;
    this->movieName = movieName;
}

void Movie::setMovieCode(std::string movieCode){
    this->movieCode = movieCode;
}

std::string Movie::getMovieCode(){
    return this->movieCode;
}

void Movie::setMovieName(std::string movieName){
    this->movieName = movieName;
}

std::string Movie::getMovieName(){
    return this->movieName;
}

void Movie::rentMovie(Renter Renters){
    int d = 0;
    for (int i = 0; i < renters.size(); i++) {
        /*
        if (renters[i].getRenterFirstName() == Renters.getRenterFirstName()){
            d += 1;
        }
        if (renters[i].getRenterLastName() == Renters.getRenterLastName()){
            d += 1;
        }
         */
        if (renters[i].getRenterID() == Renters.getRenterID()){
            d += 1;
        }
    }
    if (renters.size() >= 10) {
        throw RenterLimitException();
    }
    else if (d > 0) {
        throw DuplicateRenterException();
    }
    else {
        renters.insert(renters.end(), Renters);
    }
}

void Movie::returnRental(int renterId){
    int d = 0;
    int p = -1;
    for (int i = 0; i < renters.size(); i++) {
        if (renters[i].getRenterID() == renterId){
            d += 1;
            p = i;
        }
    }
    if (renters.size() == 0) {
        throw EmptyRenterListException();
    }
    else if (d == 0 || p < 0) {
        throw RenterNotFoundException();
    }
    else {
        renters.erase(renters.begin()+p);
    }
}

bool Movie::isBeingRented(){
    if (renters.size() > 0){
        return true;
    }
    else {
        return false;
    }
}

void Movie::printMovieInfo(){
    std::cout << "Movie Code, Movie Name: " << this->movieCode << ", "<< this->movieName << std::endl;
    if (renters.size() > 0) {
        std::cout << "Renters:" << std::endl;
        for (int i = 0; i < renters.size(); i++) {
            std::cout << "Renter ID, First Name, Last Name: " << renters[i].getRenterID() << ", " << renters[i].getRenterFirstName() << ", " << renters[i].getRenterLastName() << std::endl;
        }
    }
}
