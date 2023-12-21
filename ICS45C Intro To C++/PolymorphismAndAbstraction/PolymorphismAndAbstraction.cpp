#include <iostream>
#include "Shapes.hpp"

int main() {
    
    //Inheritance Example
    /*
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
     */
    
    //Polymorphism Example
    Shapes myShape;
    Rectangle myRectangle;
    Shapes* myShapePtr = new Shapes;
    Rectangle* myRectanglePtr = new Rectangle;
    Shapes& myShapeRef = myShape;
    Rectangle& myRectangleRef = myRectangle;

    /*
    // the rectangle object is sliced when copied to the myOtherShape - no access the printDimensions member function (takes the rectangle members not in shapes members) */
    Shapes myOtherShape = myRectangle;
    //Rectnagle myOtherRectangle = myShape
    
    
    //Pointers and Refrence in Polymorphism
    Shapes ms1; // declares a shape object
    Rectangle mr1; // declares a rectangle object
    Shapes& msr = mr1; // declaring a shapes refrence to a rectangle object
    //Rectangle& mrr = ms1; // declaring a rectangle refrence to a shapes object
    Shapes* msp = new Shapes; // declares a shapes pointer that point to a dynaically allocated shapes object
    Rectangle* mrp = new Rectangle; // declares a rectangle pointer that points to a dynamically alocated rectaangle object
    Shapes* ms2p = mrp; // declaring a shapes pointer that points to a rectangle pointer
    //Rectangle* mr2p = msp; // declaring a rectangle pointer that points to a shapes pointer
    
    //This is an exmaple of the same object (rectangle) having 2 forms of the printDimensions fucntions (basically just goes to base class right away)
    std::cout << "Shapes referencing a rectangle object" << std::endl;
    msr.printDimensions();
    std::cout << "Shapes pointing a rectangle object" << std::endl;
    ms2p->printDimensions();
    
    //Abstract/Pure Virtual Function
    // Triangle someTrig; this does not work because triangle is an abstract class
    RightTriangle someTrig;
    someTrig.helloWorld();
    
    return 0;
}
