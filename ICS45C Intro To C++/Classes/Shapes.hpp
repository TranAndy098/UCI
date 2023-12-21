// #ifndef Shapes_hpp
// #define Shapes_hpp

// #include <stdio.h>

// #endif /* Shapes_hpp */

#pragma once
// adding setters and getters lets the reader know what they can change and what they can see
class Shapes {
private:
    // defining member variables to be private
    int shapeLength; // do not have to initalize here can be down in constructor
    int shapeWidth;
public:
    // define shape constructors
    Shapes();
    Shapes(Shapes &shapes); // using the "&" is becasue we are passing in the location of myshapes
    // defining member functions to be public
    int getShapeLength(); // getter for private member shape length
    int getShapeWidth();// getter for private member shape width
    void setShapeLength(int); // setter for private member shape length
    void setShapeWidth(int); // setter for private member shape width
    int calculateArea(); // or could be calculateArea(int length, int width) to use with outside numbers and function calculates area with width and length
    int calculateDiameter(int, int); // or could be calculateDiameter(int length, int width) and function calcualtes the diameter of a shape with width and length
    
    ;
};
