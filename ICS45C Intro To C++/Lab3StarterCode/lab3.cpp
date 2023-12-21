#include "Movie.h"

using namespace std;

void test();

int main()
{
	cout << "Start testing\n" << endl;
	
    Movie movie;
    movie.printMovieInfo();
    
    movie.setMovieTime(142);
    movie.setMovieYearOut(2018);
    movie.setNumberOfActors(1);
    movie.addActor("ben", "affelck", 1992);
    movie.setMoviePrice(19.99);
    movie.setMovieTitle("Batman Forever");
    
    movie.printMovieInfo();
    
    Movie movie2(movie);
    
    movie2.printMovieInfo();
    
    movie2.setNumberOfActors(3);
    movie2.printMovieInfo();
    movie2.addActor("matt", "damon", 1995);
    movie2.printMovieInfo();
    movie2.addActor("gal", "gadot", 1987);
    movie2.printMovieInfo();
	cout << "Finished testing" << endl;
    
	return 0;
}

void test()
{

}
