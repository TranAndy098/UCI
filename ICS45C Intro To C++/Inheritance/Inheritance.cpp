#include <iostream>
#include "Shapes.hpp"

int main() {
    
    //Inheritance Example
    Shapes myFirstShape(10,10);
    Rectangle myFirstRectangle(10,10);
    Square myFirstSquare(10,10);
    RightTriangle myFirstRT(10,10,10);
    
    std::cout << "The area of my shape is " << myFirstShape.calcArea() << " meters^2. The diameter (perimater) of my shape is " << myFirstShape.calcDiameter() << " meters." << std::endl;
    std::cout << "The area of my rectangle is " << myFirstRectangle.calcArea() << " meters^2. The diameter (perimater) of my rectangle is " << myFirstRectangle.calcDiameter() << " meters." << std::endl;
    myFirstRectangle.printDimensions();
    std::cout << "The area of my square is " << myFirstSquare.calcArea() << " meters^2. The diameter (perimater) of my square is " << myFirstSquare.calcDiameter() << " meters." << std::endl;
    myFirstSquare.printDimensions();
    std::cout << "The area of my right triangle is " << myFirstRT.calcArea() << " meters^2. The diameter (perimater) of my right triangle is " << myFirstRT.calcDiameter() << " meters." << std::endl;
    
    
    return 0;
}
