// #pragma once
/*
#ifndef Cars_hpp
#define Cars_hpp

#include <stdio.h>

#endif // Cars_hpp
*/

#ifndef Cars_hpp
#define Cars_hpp

#include <string>

class Cars {
    
private:
    std::string color;
    std::string make;
    std::string model;
    int tankSize;
    int maxDistance;

public:
    std::string getColor();
    std::string getMake();
    std::string getModel();
    int getTankSize();
    int getMaxDistance();
    void setColor(std::string);
    void setMake(std::string);
    void setModel(std::string);
    void setTankSize(int);
    void setMaxDistance(int);
    Cars(); // declared a constructor to initalize without default data
    Cars(Cars&); // declared a constructor that takes an existing object as the source data
    Cars(std::string, std::string, std::string, int,int); // decalred a constructor that takes in initial values
    
};
#endif // Cars_hpp
