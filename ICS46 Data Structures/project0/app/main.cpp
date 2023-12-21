#include "proj0.hpp"
#include <unordered_map>
#include <string>
#include <iostream>
#include <math.h>

// Note:  you are not required to implement a main() for this project.
//      Feel free to create one; it will not be accounted for in grading.
//      Be sure to use the unit testing process to test your code: that is
//      how we will be grading. 

int main()
{
    std::string s1 = "POT";
    std::string s2 = "PAN";
    std::string s3 = "BIB";
    std::unordered_map<char, unsigned> solution = { {'A', 7}, {'B', 5}, {'I', 0}, {'N', 4}, {'O', 3}, {'P', 2}, {'T', 1}};
    std::cout << s1 << " + " << s2 << " = " << s3 << " : " << std::boolalpha << verifySolution(s1, s2, s3, solution) << std::endl;
    
    std::string s11 = "JAJ";
    std::string s21 = "JJE";
    std::string s31 = "JAE";
    std::unordered_map<char, unsigned> solution2 = { {'A', 1}, {'B', 2}, {'C', 3}, {'D', 4}, {'E', 5}, {'F', 6}, {'G', 7}, {'H', 8}, {'I', 9}, {'J', 0}};
    std::cout << s11 << " + " << s21 << " = " << s31 << " : " << std::boolalpha << verifySolution(s11, s21, s31, solution2) << std::endl;

    std::string s12 = "AII";
    std::string s22 = "A";
    std::string s32 = "BJJ";
    std::cout << s12 << " + " << s22 << " = " << s32 << " : " << std::boolalpha << verifySolution(s12, s22, s32, solution2) << std::endl;

    std::string s13 = "EDCBA";
    std::string s23 = "JIHGF";
    std::string s33 = "FDAIG";
    std::cout << s13 << " + " << s23 << " = " << s33 << " : " << std::boolalpha << verifySolution(s13, s23, s33, solution2) << std::endl;

    std::string s14 = "JJJJJ";
    std::string s24 = "JJJJJ";
    std::string s34 = "A";
    std::cout << s14 << " + " << s24 << " = " << s34 << " : " << std::boolalpha << verifySolution(s14, s24, s34, solution2) << std::endl;
    return 0;
}



