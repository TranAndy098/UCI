#include "Actor.h"

using namespace std;

Actor::Actor() {
    this->firstName = "First";
    this->lastName = "Last";
    this->birthYear = 0;
}

Actor::Actor(std::string first, std::string last, int year) {
    this->firstName = first;
    this->lastName = last;
    this->birthYear = year;
}

void Actor::setFirstName(std::string first) {
    this->firstName = first;
}

std::string Actor::getFirstName() {
    return this->firstName;
}

void Actor::setLastName(std::string last) {
    this->lastName = last;
}

std::string Actor::getLastName() {
    return this->lastName;
}

void Actor::setBirthYear(int year) {
    this->birthYear = year;
}

int Actor::getBirthYear() {
    return this->birthYear;
}

