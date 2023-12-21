#include "proj0.hpp"


bool verifySolution(std::string s1, std::string s2, std::string s3, const std::unordered_map<char, unsigned> & mapping)
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





