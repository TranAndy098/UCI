#include <iostream>
#include "Cars.hpp"
#include "Vans.h"

int main() {
    Cars myFirstCar("Black", "Honda", "Accord", 15, 450);


    myFirstCar.setMake("Tesla");
    myFirstCar.setModel("Model X");

    std::cout << "My first car is a " << myFirstCar.getColor() << " " << myFirstCar.getMake() << " "
        << myFirstCar.getModel() << " that can travel " << myFirstCar.getMaxDistance() << " miles using "
        << myFirstCar.getTankSize() << " gallons of gas." << std::endl;

    std::cout << "Printing Object Directory: " << &myFirstCar << std::endl;

    std::cout << "Printing Object: " << myFirstCar << std::endl;
    
    return 0;
}
