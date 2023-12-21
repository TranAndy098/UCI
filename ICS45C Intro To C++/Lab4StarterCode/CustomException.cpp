#include "CustomException.h"

const char* DuplicateMovieException::what(){
    return "A Movie already exists with that name, all new movies must have unique movie name";
}

const char* DuplicateRenterException::what(){
    return "A Renter already exists with that name and/or id, all new renters must have unique name and id";
}

const char* EmptyMovieInfoException::what(){
    return "Movie Code and/or Movie Name is empty, all new movies must have a non empty movie code and movie name";
}

const char* EmptyMovieListException::what(){
    return "Movie List is empty, attempting to discontinue a movie can only be done when movie list has at least one movie";
}

const char* EmptyRenterListException::what(){
    return "Renter List is empty, attempting to return a movie can only be done when renter list has at least one renter";
}

const char* EmptyRenterNameException::what(){
    return "Renter First Name and/or Renter Last Name is empty, all new renter must have a non empty first name and last name";
}

const char* InvalidRenterIDException::what(){
    return "Renter ID is invalid, renter id exists already so movie can not be rented or does not exist so movie can not be returned";
}

const char* MovieLimitException::what(){
    return "Movie cannot be added, the movie list is already at its max capacity";
}

const char* MovieNotFoundException::what(){
    return "Actions can not be performed, the movie does not exists in the movie list";
}

const char* RentedMovieException::what(){
    return "Movie cannot be discontinue, the movie is currently rented";
}

const char* RenterLimitException::what(){
    return "Renter cannot rent movie, there are no more available copies for renter";
}

const char* RenterNotFoundException::what(){
    return "Renter cannot be removed, renter does not exists in renter list";
}

