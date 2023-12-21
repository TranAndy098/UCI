#include "Wordset.hpp"
#include <string>
#include <cstring>
#include <math.h>

// returns s, as a number in the given base, mod the given modulus
unsigned polynomialHashFunction(const std::string & s, unsigned base, unsigned mod)
{
	int size = s.size(); // use size constantly to determine tens, hundreds
    unsigned result = 0; // we will add as needed

    // go through, get letter mappings and add to result
    for (int i = 0; i < size; ++i) {
        result +=  (s[i] - 'a' + 1);
        if (i < size - 1)
            result *= base;
        result = result % mod;
    }

    return result % mod;
}




WordSet::WordSet(unsigned initialCapacity, unsigned evictionThreshold)
{
	// assign cap and threshhold
	_capacity = initialCapacity;
	_evictionThreshold = evictionThreshold;

	// dynamicall allocate our tables
	_table1 = new char *[_capacity] {nullptr};
	_table2 = new char *[_capacity] {nullptr};
}

// helper funtion to deallocate 2 list of c strings
void WordSet::deallocate(char **arr1, char **arr2, unsigned capacity)
{
	// delete all words in the tables
	for (unsigned i=0; i < capacity; ++i) {
		delete arr1[i];
		delete arr2[i];
	}

	// delete the tables
	delete arr1;
	delete arr2;
}

WordSet::~WordSet()
{
	deallocate(_table1, _table2, _capacity); // free memory
}

bool WordSet::isPrime(unsigned num)
{
	for (unsigned i=2; i<=sqrt(num); ++i)
		if (num % i == 0)
			return false;

	return true;
}

// return next prime that is at least twice the sice of current prime
unsigned WordSet::getNextPrime(unsigned prime)
{
	unsigned i;
	// increment i till prime
	for (i=2*prime+1; !isPrime(i); i+=2) {}

	return i;
}

// resize our tables to new capacity and copy everything over
void WordSet::resize()
{
	// temp variable to point at the existing memory
	char **temp1 = _table1;
	char **temp2 = _table2;


	// allocate new memory for tables
	unsigned oldCapacity = _capacity;
	_capacity = getNextPrime(_capacity);
	_uniqueCount = 0;
	_table1 = new char *[_capacity] {nullptr};
	_table2 = new char *[_capacity] {nullptr};

	// copy over all old data
	for (unsigned i=0; i<oldCapacity; ++i) {
		if (temp1[i] != nullptr)
			insert(std::string(temp1[i]));

		if (temp2[i] != nullptr)
			insert(std::string(temp2[i]));
	}

	// free old memory
	deallocate(temp1, temp2, oldCapacity);
}

void WordSet::insert(const std::string & s)
{
	// if this string is not already contained, increment unique count
	if (contains(s))
		return;

	std::string oldWord, newWord;
	newWord = s;
	unsigned currTable = 1;
	unsigned numCollisions = 0;
	bool inserted = false;
	while (!inserted) {
		// resize because we ran out of allowed collisions
		if (numCollisions == _evictionThreshold) {
			resize();
			numCollisions = 0;
			currTable = 1;
		}

		if (currTable == 1) {
			// hash and check table 1
			unsigned h1Index = polynomialHashFunction(newWord, BASE_H1, _capacity);

			// if table 1 has collisiony
			if (_table1[h1Index] != nullptr) {
				currTable = 2; // now we need next table
				++numCollisions; // one less collision allowed
				oldWord = std::string(_table1[h1Index]); // now string must move
				delete _table1[h1Index]; // delete so we can allocate correct size
			}
			else
				inserted = true;

			// allocate space for new word and cpy in
			_table1[h1Index] = new char[newWord.size() + 1];
			std::strcpy(_table1[h1Index], newWord.c_str());
			newWord = oldWord; // newWord become old word since we are going to next table
		}
		else {
			// hash and check table 2
			unsigned h2Index = polynomialHashFunction(newWord, BASE_H2, _capacity);

			// if table 2 has collisiony
			if (_table2[h2Index] != nullptr) {
				currTable = 1; // now we need next table
				++numCollisions; // one less collision allowed
				oldWord = std::string(_table2[h2Index]); // now string must move
				delete _table2[h2Index]; // delete so we can allocate correct size
			}
			else
				inserted = true;

			// allocate space for new word and cpy in
			_table2[h2Index] = new char[newWord.size() + 1];
			std::strcpy(_table2[h2Index], newWord.c_str());
			newWord = oldWord; // newWord become old word since we are going to next table
		}
	}

	++_uniqueCount;
}


bool WordSet::contains(const std::string & s) const
{
	bool rtn = false;

	// hash with base 1 and check if its in table1
	unsigned h1Index = polynomialHashFunction(s, BASE_H1, _capacity);
	if (_table1[h1Index] != nullptr && std::strcmp(_table1[h1Index], s.c_str()) == 0)
		rtn = true;

	// hash with base 2 and check if its in table2
	unsigned h2Index = polynomialHashFunction(s, BASE_H2, _capacity);
	if (_table2[h2Index] != nullptr && std::strcmp(_table2[h2Index], s.c_str()) == 0)
		rtn = true;

	return rtn; 
}

// return how many distinct strings are in the set
unsigned WordSet::getCount() const
{
	return _uniqueCount; 
}

// return how large the underlying array is.
unsigned WordSet::getCapacity() const
{
	return _capacity;
}
