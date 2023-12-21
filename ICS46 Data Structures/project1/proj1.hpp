#ifndef __PROJ_1__HPP
#define __PROJ_1__HPP

#include <unordered_map>
#include <math.h>


/* 
 * Project 1:  you need to implement this function.
 I promise that any of my test cases will have an empty 
 	map as the fourth parameter when called.
 If the puzzle IS solvable, return true AND make the mapping indicate the solution.
 If the puzzle is NOT solvable, it is enough to return false.

 See the project 1 write-up for a better description. 
 */


bool puzzleSolver(std::string s1, std::string s2, std::string s3, std::unordered_map<char, unsigned> & mapping);

bool pieceSolver(std::string s1, std::string s2, std::string s3, std::unordered_map<char, unsigned> & mapping, std::vector<char> charRemain, std::vector<int> digitRemain);
bool verifySol(std::string s1, std::string s2, std::string s3, std::unordered_map<char, unsigned> & mapping);

#endif
