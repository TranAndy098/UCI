#include <iostream>
#include "Shapes.hpp"

int main() {
    
    Shapes myShape;
    Shapes myCopiedShape1(myShape); // copying it here will have the orignal values before changes
    std::cout << "Size of myShape: " << sizeof(myShape) << std::endl;
    std::cout << "Printing starting address myShape: " << &myShape << std::endl; // "&" in front of a object tells you the memory location
    //std::cout << "Printing memory address of shapeLength: " << &myShape.shapeLength << std::endl;
    //std::cout << "Printing memory address of shapeWidth: " << &myShape.shapeWidth << std::endl;
    std::cout << "Getting shapeLength before setting: " << myShape.getShapeLength() << std::endl;
    std::cout << "Getting shapeWidth before setting: " << myShape.getShapeWidth() << std::endl;
    myShape.setShapeLength(5);
    myShape.setShapeWidth(10);
    std::cout << "Getting shapeLength after setting: " << myShape.getShapeLength() << std::endl;
    std::cout << "Getting shapeWidth after setting: " << myShape.getShapeWidth() << std::endl;
    std::cout << "Calculate Area: " << myShape.calculateArea() << std::endl;
    std::cout << "Calculate Stored Diameter: " << myShape.calculateDiameter(myShape.getShapeLength(),myShape.getShapeWidth()) << std::endl; // using the get functions can get the length and width that is stored
    std::cout << "Calculate Our Own Diameter: " << myShape.calculateDiameter(5,10) << std::endl; // we can pass in out own numbers to caluclate diameter (perimeter)
    
    Shapes myCopiedShape2(myShape); // copying it here will have the changed values
    myCopiedShape2.setShapeLength(10);
    
    std::cout << "Getting Copied 1 shapeLength after setting: " << myCopiedShape1.getShapeLength() << std::endl;
    std::cout << "Getting Copied 1 shapeWidth after setting: " << myCopiedShape1.getShapeWidth() << std::endl;
    std::cout << "Calculate Copied 1 Area: " << myCopiedShape1.calculateArea() << std::endl;
    std::cout << "Calculate Copied 1 Stored Diameter: " << myCopiedShape1.calculateDiameter(myCopiedShape1.getShapeLength(),myCopiedShape1.getShapeWidth()) << std::endl;
    std::cout << "Calculate Our Own Diameter with Copied 1 Function: " << myCopiedShape1.calculateDiameter(5,10) << std::endl;
    
    std::cout << "Getting Copied 2 shapeLength after setting: " << myCopiedShape2.getShapeLength() << std::endl;
    std::cout << "Getting Copied 2 shapeWidth after setting: " << myCopiedShape2.getShapeWidth() << std::endl;
    std::cout << "Calculate Copied 2 Area: " << myCopiedShape2.calculateArea() << std::endl;
    std::cout << "Calculate Copied 2 Stored Diameter: " << myCopiedShape2.calculateDiameter(myCopiedShape2.getShapeLength(),myCopiedShape2.getShapeWidth()) << std::endl;
    std::cout << "Calculate Our Own Diameter with Copied 2 Function: " << myCopiedShape2.calculateDiameter(5,10) << std::endl;
    
    return 0;
}
