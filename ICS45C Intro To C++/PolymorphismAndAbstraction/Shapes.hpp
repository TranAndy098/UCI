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
    virtual void printDimensions(); // having virtual infront means it will override base class funtion with a derived class's function of the same name
};

// rectangle class will be dervied/child/ "is a shape" class
class Rectangle: public Shapes {
public:
    Rectangle();
    Rectangle(int,int);
    void printDimensions() override; // having override means that it will override the function from the base class of the same name and in the base class it must be a virtual function
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
    virtual void helloWorld() = 0; // pure virutal is a way to declare a function that a child/derived must define and making it an abstract class

};

class RightTriangle: public Triangle, Square{
public:
    RightTriangle();
    RightTriangle(int,int,int);
    int calcArea();
    int calcDiameter();
    void helloWorld() override;
};

#endif /* Shapes_hpp */
