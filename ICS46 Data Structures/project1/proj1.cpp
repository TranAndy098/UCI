#include "proj1.hpp"
#include <unordered_map>
#include <string>

#include <vector>


bool puzzleSolver(std::string s1, std::string s2, std::string s3, std::unordered_map<char, unsigned> & mapping)
{
    std::vector<int> digitRemained (10);
    
    for (int i = 0; i < 10; i++) {
        digitRemained[i] = i;
    }
    
    std::string s = "";
    
    for (int i = 0; i < s1.length(); i++) {
        if ((s.find(s1[i]) != std::string::npos) == 0) {
            s += s1[i];
        }
    }
    for (int i = 0; i < s2.length(); i++) {
        if ((s.find(s2[i]) != std::string::npos) == 0) {
            s += s2[i];
        }
    }
    for (int i = 0; i < s3.length(); i++) {
        if ((s.find(s3[i]) != std::string::npos) == 0) {
            s += s3[i];
        }
    }
    
    std::vector<char> charRemained (s.length());
    
    for (int i = 0; i < sizeof(charRemained) ; i++) {
        charRemained[i] = s[i];
    }
    
    
    return pieceSolver(s1,s2,s3,mapping, charRemained, digitRemained);
}

bool pieceSolver(std::string s1, std::string s2, std::string s3, std::unordered_map<char, unsigned> & mapping, std::vector<char> charRemain, std::vector<int> digitRemain) {
    if (charRemain.size() == 0) {
        return verifySol(s1,s2,s3,mapping);
    }
    else {
        std::vector<int> digitRemained (digitRemain.size());
        digitRemained = digitRemain;
        char currChar = charRemain[0];
        charRemain.erase(charRemain.begin());
        for (int i = 0; i < digitRemain.size(); i++) {
            int d = digitRemain[i];
            digitRemain.erase(digitRemain.begin() + i);
            mapping[currChar] = d;
            if ((pieceSolver(s1,s2,s3,mapping, charRemain, digitRemain)) == true ) {
                return true;
            }
            else {
                digitRemain = digitRemained;
                mapping.erase(currChar);
            }
        }
    }
    
    return false; // This is not the correct general solution.
}

bool verifySol(std::string s1, std::string s2, std::string s3, std::unordered_map<char, unsigned> & mapping)
{
    bool works = false;
    int a = 0;
    int b = 0;
    int c = 0;
    
    unsigned long s1l = s1.length();
    int aplace = (int)s1l;
    
    for (int i = 0; i < s1.length(); i++){
        aplace -= 1;
        a += (mapping.at(s1[i])) * pow(10,aplace);
    }
    
    unsigned long s2l = s2.length();
    int bplace = (int)s2l;
    for (int i = 0; i < s2.length(); i++){
        bplace -= 1;
        b += (mapping.at(s2[i])) * pow(10,bplace);
    }

    unsigned long s3l = s3.length();
    
    int cplace = (int)s3l;
    for (int i = 0; i < s3.length(); i++){
        cplace -= 1;
        c += (mapping.at(s3[i])) * pow(10,cplace);
    }

    if (a + b == c) {
        works = true;
    }

    return works; // FYI, this stub is not a correct solution.
}

