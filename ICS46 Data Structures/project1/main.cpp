// If you really want to make a program for the app, be my guest.
// You may prefer to do so in /exp instead.
// Or better yet, use gtest to automate your own test cases!

#include "proj1.hpp"
#include <unordered_map>
#include <string>

#include <iostream>

int main()
{
    std::unordered_map<char, unsigned> puzzle2;
    
    bool p2 = puzzleSolver("UCI", "ALEX", "MIKE", puzzle2);
    std::cout << p2<< std::endl;
    for (auto it = puzzle2.cbegin(); it != puzzle2.cend(); it++) {
        std::cout << "{" << (*it).first << ": " << (*it).second << "}\n";
    }
    
    std::cout << "\n";
    
    std::unordered_map<char, unsigned> puzzle;
    
    bool p = puzzleSolver("KUCI", "ALEX", "MIKE", puzzle);
    std::cout << p << std::endl;
    
    for (auto it = puzzle.cbegin(); it != puzzle.cend(); it++) {
        std::cout << "{" << (*it).first << ": " << (*it).second << "}\n";
    }
    
    std::cout << "\n";

    std::unordered_map<char, unsigned> puzzle3;
    
    bool p3 = puzzleSolver("LARRY", "CAREER", "LEGEND", puzzle3);
    std::cout << p3 << std::endl;
    
    for (auto it = puzzle3.cbegin(); it != puzzle3.cend(); it++) {
        std::cout << "{" << (*it).first << ": " << (*it).second << "}\n";
    }
    return 0;
}



