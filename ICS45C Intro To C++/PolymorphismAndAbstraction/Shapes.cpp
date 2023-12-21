#include "Shapes.hpp"


Shapes::Shapes(){
    this->width = 0;
    this->height = 0;
}

Shapes::Shapes(int width, int height){
    this->width = width;
    this->height = height;
}

int Shapes::calcDiameter(){
    return (2 * this->width) + (2 * this->height);
}

int Shapes::calcArea(){
    return this->width * this->height;
}

void Shapes::printDimensions(){
    std::cout << "Shapes Height is " << this->height << " meters and Shapes Width is " << this->width << " meters." << std::endl;
}

Rectangle::Rectangle(){
    this->width = 0;
    this->height = 0;
}

Rectangle::Rectangle(int width, int height){
    this->width = width;
    this->height = height;
}

void Rectangle::printDimensions(){
    std::cout << "Rectangle Height is " << this->height << " meters and Rectangle Width is " << this->width << " meters." << std::endl;
}

Square::Square(){
    this->width = 0;
    this->height = 0;
}

Square::Square(int width, int height){
    this->width = width;
    this->height = height;
}

RightTriangle::RightTriangle(){
    this->diagonalLength = 0;
    this->width = 0;
    this->height = 0;
}

RightTriangle::RightTriangle(int width, int height, int diagonalLength){
    this->width = width;
    this->height = height;
    this->diagonalLength = diagonalLength;
}

int RightTriangle::calcArea(){
    return .5 * this->width * this->height;
}

int RightTriangle::calcDiameter(){
    return this->diagonalLength + this->width + this->height;
}

void RightTriangle::helloWorld(){
    std::cout << "hello pure virtual world" << std::endl;
}
