#include "Movie.h"

using namespace std;

Movie::Movie() {
    this->movieTime = 0;
    this->movieYearOut = 0;
    this->numberOfActors = 0;
    this->actorArrayIndex = 0;
    this->moviePrice = 0.0;
    this->movieTitle = "Title";
    this->actors = new Actor[this->numberOfActors];
}

Movie::Movie(int time, int year, int actors, double price, std::string title) {
    this->movieTime = time;
    this->movieYearOut = year;
    this->numberOfActors = actors;
    this->actorArrayIndex = 0;
    this->moviePrice = price;
    this->movieTitle = title;
    this->actors = new Actor[this->numberOfActors];
}

Movie::Movie(const Movie &m) {
    this->movieTime = m.movieTime;
    this->movieYearOut = m.movieYearOut;
    this->numberOfActors = m.numberOfActors;
    this->actorArrayIndex = 0;
    this->moviePrice = m.moviePrice;
    this->movieTitle = m.movieTitle;
    this->actors = new Actor[this->numberOfActors];
    for (int i = 0; i < m.actorArrayIndex; i++) {
        addActor(m.actors[i].getFirstName(), m.actors[i].getLastName(), m.actors[i].getBirthYear());
    }
}

Movie::~Movie() {
    delete [] this->actors;
}

void Movie::setMovieTime(int time) {
    this->movieTime = time;
}

int Movie::getMovieTime() {
    return this->movieTime;
}

void Movie::setMovieYearOut(int year) {
    this->movieYearOut = year;
}

int Movie::getMovieYearOut() {
    return this->movieYearOut;
}

void Movie::setNumberOfActors(int actors) {
    this->numberOfActors = actors;
    Actor *a = this->actors;
    this->actors = new Actor[this->numberOfActors];
    for (int i = 0; i < this->actorArrayIndex; i++) {
        this->actors[i].setFirstName(a[i].getFirstName());
        this->actors[i].setLastName(a[i].getLastName());
        this->actors[i].setBirthYear(a[i].getBirthYear());}
    delete [] a;
}

int Movie::getNumberOfActors() {
    return this->numberOfActors;
}

void Movie::addActor(std::string first, std::string last, int year) {
    int b = 0;
    b = this->actorArrayIndex;
    this->actorArrayIndex = this->actorArrayIndex + 1;
    this->actors[b].setFirstName(first);
    this->actors[b].setLastName(last);
    this->actors[b].setBirthYear(year);
    
}

void Movie::setMoviePrice(double price) {
    this->moviePrice = price;
}

double Movie::getMoviePrice() {
    return this->moviePrice;
}

void Movie::setMovieTitle(std::string title) {
    this->movieTitle = title;
}

std::string Movie::getMovieTitle() {
    return this->movieTitle;
}

void Movie::printMovieInfo() {
    std::cout << "Title: " << this->movieTitle << ", Published in: " << this->movieYearOut << std::endl;
    std::cout << "Duration of Movie: " << this->movieTime << " minutes" << std::endl;
    std::cout << "Price: $" << this->moviePrice << std::endl;
    std::cout << "Actors:" << std::endl;
    for (int i = 0; i < this->actorArrayIndex; i++){
        std::cout << this->actors[i].getFirstName() << " " << this->actors[i].getLastName() << ", " << this->actors[i].getBirthYear() << std::endl;
    }
}
