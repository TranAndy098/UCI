#ifndef __WORD_SET___HPP
#define __WORD_SET___HPP


#include <string>

// You may assume, in writing this function, that the given
// string consists solely of lower-case letters.

// To get the "number" that a letter-digit represents,
// subtract 'a' from it.
// e.g., (s[0]-'a') is the most significant "digit" of s.
// That would give you a 0 for a, etc;  add one to get 'a' = 1, 'b' = 2, etc. 

// After every "digit" is processed, mod the current value by mod.
// This will keep you from having overflow.
unsigned polynomialHashFunction(const std::string & s, unsigned base, unsigned mod);


class WordSet
{
public: 
	explicit WordSet(unsigned initialCapacity, unsigned evictionThreshold = DEFAULT_EVICT_THRESHOLD);
	~WordSet();

	// adds the given string to the WordSet, so that any 
	// future calls to contains(s) will return true.
	// Note that we are not implementing remove in this
	// project.
	// 
	void insert(const std::string & s);

	bool contains(const std::string & s) const;

	// return how many distinct strings are in the set
	unsigned getCount() const; 

	// return how large the underlying array is.
	unsigned getCapacity() const;

private:
	static constexpr unsigned BASE_H1 = 37;
	static constexpr unsigned BASE_H2 = 41; 
	static constexpr unsigned DEFAULT_EVICT_THRESHOLD = 5; 

	// You may declare private functions and member variables here.
	// our tables, capacity, count, and eviction threshhold
	char ** _table1 = nullptr;
	char ** _table2 = nullptr;
	unsigned _capacity = 0;
	unsigned _uniqueCount = 0;
	unsigned _evictionThreshold = DEFAULT_EVICT_THRESHOLD;

	unsigned getNextPrime(unsigned prime);
	bool isPrime(unsigned num);
	void resize(); // function to resize our internal char arrays
	void deallocate(char **, char**, unsigned); // helper functoin to deallocate list of c strings
};


#endif
