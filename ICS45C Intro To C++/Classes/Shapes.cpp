#include "Shapes.hpp"

// this-> is like self. and should always be used, it might work without but best to use it

// default constuctor that sets a new value
Shapes::Shapes() {
    this->shapeLength = 0;
    this->shapeWidth = 0;
}

// constuctor with passed in arguments
// using the "&" is becasue we are passing in the location of myShape
Shapes::Shapes(Shapes &myShape) {
    this->shapeLength = myShape.getShapeLength();
    this->shapeWidth = myShape.getShapeWidth();
}

int Shapes::getShapeLength() {
    return this->shapeLength;
}

int Shapes::getShapeWidth() {
    return this->shapeWidth;
}

void Shapes::setShapeLength(int shapeLength) {
    this->shapeLength = shapeLength;
}

void Shapes::setShapeWidth(int shapeWidth) {
    this->shapeWidth = shapeWidth;
}

int Shapes::calculateArea() {
    return (this->shapeLength * this->shapeWidth);
}

int Shapes::calculateDiameter(int shapeLength, int shapeWidth) {
    return (shapeLength * 2 + shapeWidth * 2);
}

