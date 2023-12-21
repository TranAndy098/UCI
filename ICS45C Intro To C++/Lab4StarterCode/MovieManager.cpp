#include "MovieManager.h"

void MovieManager::run(){
    bool on = true;
    std::string input;
    while (on == true) {
        mmUI.printMenu();
        input = mmUI.getCommand();
        mmUI.enterToContinue();
        if (input == "Q"){
            on = false;
        }
        else {
            try {
                if (input == "AM"){
                    std::string mn;
                    std::string mc;
                    mc = mmUI.getMovieCode();
                    mn = mmUI.getMovieName();
                    addMovie(Movie(mc,mn));
                }
                else if (input == "DM"){
                    std::string mc;
                    mc = mmUI.getMovieCode();
                    discontinueMovie(mc);
                }
                else if (input == "RM"){
                    std::string fn;
                    std::string ln;
                    int ri;
                    std::string mc;
                    mc = mmUI.getMovieCode();
                    ri = mmUI.getRenterID();
                    fn = mmUI.getRenterFirstName();
                    ln = mmUI.getRenterLastName();
                    rentMovie(mc, Renter(ri, fn, ln));
                }
                else if (input == "RR"){
                    std::string mc;
                    int ri;
                    mc = mmUI.getMovieCode();
                    ri = mmUI.getRenterID();
                    returnRental(ri, mc);
                }
                else if (input == "P"){
                    printInventory();
                }
            }
            catch (DuplicateMovieException& e) {
                mmUI.print(e.what());
            }
            catch (DuplicateRenterException& e) {
                mmUI.print(e.what());
            }
            catch (EmptyMovieInfoException& e) {
                mmUI.print(e.what());
            }
            catch (EmptyMovieListException& e) {
                mmUI.print(e.what());
            }
            catch (EmptyRenterListException& e) {
                mmUI.print(e.what());
            }
            catch (EmptyRenterNameException& e) {
                mmUI.print(e.what());
            }
            catch (InvalidRenterIDException& e) {
                mmUI.print(e.what());
            }
            catch (MovieLimitException& e) {
                mmUI.print(e.what());
            }
            catch (MovieNotFoundException& e) {
                mmUI.print(e.what());
            }
            catch (RentedMovieException& e) {
                mmUI.print(e.what());
            }
            catch (RenterLimitException& e) {
                mmUI.print(e.what());
            }
            catch (RenterNotFoundException& e) {
                mmUI.print(e.what());
            }
            catch (...) {
                mmUI.print("Other Exception");
            }
            
        }
    }
    
}

void MovieManager::addMovie(Movie m){
    int d = 0;
    for (int i = 0; i < movies.size(); i++) {
        if (movies[i].getMovieCode() == m.getMovieCode()){
            d += 1;
        }
        if (movies[i].getMovieName() == m.getMovieName()){
            d += 1;
        }
    }
    if (movies.size() >= 20){
        throw MovieLimitException();
    }
    else if (m.getMovieCode() == "" || m.getMovieName() == ""){
        throw EmptyMovieInfoException();
    }
    else if (d > 0){
        throw DuplicateMovieException();
    }
    else{
        movies.insert(movies.end(), m);
    }
}

void MovieManager::discontinueMovie(std::string movieCode){
    int d = 0;
    int p = -1;
    for (int i = 0; i < movies.size(); i++) {
        if (movies[i].getMovieCode() == movieCode){
            d += 1;
            p = i;
        }
    }
    if (movies.size() == 0) {
        throw EmptyMovieListException();
    }
    else if (d == 0 || p < 0) {
        throw MovieNotFoundException();
    }
    else if (movies[p].isBeingRented() == true) {
        throw RentedMovieException();
    }
    else {
        movies.erase(movies.begin()+p);
    }
}

void MovieManager::rentMovie(std::string movieCode, Renter s){
    int dr = 0;
    int p = -1;
    bool me = false;
    for (int i = 0; i < movies.size(); i++) {
        if (movies[i].getMovieCode() == movieCode) {
            me = true;
            p = i;
        }
        for (int o = 0; o < movies[i].renters.size(); o++) {
            if (movies[i].renters[o].getRenterID() == s.getRenterID()){
                dr += 1;
            }
    }
    }
    if (me == false || p < 0) {
        throw MovieNotFoundException();
    }
    else if (dr > 0) {
        throw DuplicateRenterException();
    }
    else if (s.getRenterFirstName() == "" || s.getRenterLastName() == "") {
        throw EmptyRenterNameException();
    }
    else if (s.getRenterID() < 0) {
        throw InvalidRenterIDException();
    }
    else {
        movies[p].rentMovie(s);
    }
}

void MovieManager::returnRental(int renterId, std::string movieCode){
    int er = 0;
    int p = -1;
    bool me = false;
    for (int i = 0; i < movies.size(); i++) {
        if (movies[i].getMovieCode() == movieCode) {
            me = true;
            p = i;
        }
        for (int o = 0; o < movies[i].renters.size(); o++) {
            if (movies[i].renters[o].getRenterID() == renterId){
                er += 1;
            }
    }
    }
    if (me == false || p < 0) {
        throw MovieNotFoundException();
    }
    else if (renterId < 0) { //er == 0 || 
        throw InvalidRenterIDException();
    }
    else {
        movies[p].returnRental(renterId);
    }
}

void MovieManager::printInventory(){
    mmUI.print("Movie Inventory:");
    if (movies.size() > 0) {
        for (int i = 0; i < movies.size(); i++) {
            std::string movienum;
            movienum = "Movie " + std::to_string(i+1) + ":";
            mmUI.print(movienum);
            movies[i].printMovieInfo();
        }
    }
    mmUI.print("");
}

