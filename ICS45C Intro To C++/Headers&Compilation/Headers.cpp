#include <iostream>
#include "Cars.hpp"
#include "Vans.hpp"

int main() {
    Cars myFirstCar;
    Cars mySecondCar(myFirstCar);
    Cars myThirdCar(myFirstCar.getColor(),myFirstCar.getMake(),myFirstCar.getModel(),myFirstCar.getTankSize(),myFirstCar.getMaxDistance());
    Cars myFourthCar("Black", "Honda", "Accord", 15, 450);
    
    mySecondCar.setMake("Tesla");
    mySecondCar.setModel("Model X");
    
    std::cout << "My first car is a " << myFirstCar.getColor() << " " << myFirstCar.getMake() << " " << myFirstCar.getModel() << " that can travel " << myFirstCar.getMaxDistance() << " miles using " << myFirstCar.getTankSize() << " gallons of gas." << std::endl;
    
    std::cout << "My second car is a " << mySecondCar.getColor() << " " << mySecondCar.getMake() << " " << mySecondCar.getModel() << " that can travel " << mySecondCar.getMaxDistance() << " miles using " << mySecondCar.getTankSize() << " gallons of gas." << std::endl;
    
    std::cout << "My third car is a " << myThirdCar.getColor() << " " << myThirdCar.getMake() << " " << myThirdCar.getModel() << " that can travel " << myThirdCar.getMaxDistance() << " miles using " << myThirdCar.getTankSize() << " gallons of gas." << std::endl;
    
    std::cout << "My fourth car is a " << myFourthCar.getColor() << " " << myFourthCar.getMake() << " " << myFourthCar.getModel() << " that can travel " << myFourthCar.getMaxDistance() << " miles using " << myFourthCar.getTankSize() << " gallons of gas." << std::endl;
    
    return 0;
}
