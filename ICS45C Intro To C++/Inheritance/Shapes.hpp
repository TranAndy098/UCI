#ifndef Shapes_hpp
#define Shapes_hpp

#include <stdio.h>
#include <iostream>
// shapes will be base class
class Shapes {
public:
    int width;
    int height;
    Shapes();
    Shapes(int,int);
    int calcDiameter(); // is perimeter
    int calcArea();
};

// rectangle class will be dervied/child/ "is a shape" class
class Rectangle: public Shapes {
public:
    Rectangle();
    Rectangle(int,int);
    void printDimensions();
};

// square class will be dervied/child/ "is a rectangle" class
class Square: public Rectangle {
public:
    Square();
    Square(int,int);
    //void printDimensions();
};

// define a triange base class
class Triangle {
public:
    int diagonalLength;
};

class RightTriangle: public Triangle, Square{
public:
    RightTriangle();
    RightTriangle(int,int,int);
    int calcArea();
    int calcDiameter();
};

#endif /* Shapes_hpp */
