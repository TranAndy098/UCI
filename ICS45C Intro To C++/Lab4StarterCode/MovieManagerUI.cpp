#include "MovieManagerUI.h"
#include <iostream>

std::string MovieManagerUI::toUpper(std::string input){
    for (int i =0; i < input.size(); i++){
        input.at(i) = toupper(input.at(i));
    }
    return input;
}

void MovieManagerUI::printMenu(){
    std::cout << "am: Add Movie\ndm: Discontinue Movie\nrm: Rent Movie\nrr: Return Rental\np: Print Movie Inventory\nq: Quit Program\n----------\nEnter Command:" << std::endl;
}

std::string MovieManagerUI::getCommand(){
    bool correct = false;
    std::string input;
    while (correct == false) {
        std::cin >> input;
        input = toUpper(input);
        if (input == "AM"){
            correct = true;
        }
        else if (input == "DM"){
            correct = true;
        }
        else if (input == "RM"){
            correct = true;
        }
        else if (input == "RR"){
            correct = true;
        }
        else if (input == "P"){
            correct = true;
        }
        else if (input == "Q"){
            correct = true;
        }
        else {
            invalidSelection();
        }
    }
    return input;
}

std::string MovieManagerUI::getMovieName(){
    std::cout << "Enter Movie Name:" << std::endl;
    std::string input;
    std::cin >> input;
    return input;
}

std::string MovieManagerUI::getMovieCode(){
    std::cout << "Enter Movie Code:" << std::endl;
    std::string input;
    std::cin >> input;
    return input;
}

int MovieManagerUI::getRenterID(){
    std::cout << "Enter Renter ID:" << std::endl;
    int input;
    std::cin >> input;
    return input;
}

std::string MovieManagerUI::getRenterFirstName(){
    std::cout << "Enter Renter First Name:" << std::endl;
    std::string input;
    std::cin >> input;
    return input;
}

std::string MovieManagerUI::getRenterLastName(){
    std::cout << "Enter Renter Last Name:" << std::endl;
    std::string input;
    std::cin >> input;
    return input;
}

void MovieManagerUI::invalidSelection(){
    std::cout << "Invalid Selction, Enter Command:" << std::endl;
}

void MovieManagerUI::enterToContinue(){ // ask what to do here
    std::cout << "Processing Command..." << std::endl;
}

void MovieManagerUI::print(std::string input){
    std::cout << input << std::endl;
}
