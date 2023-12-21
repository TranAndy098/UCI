#include <iostream>
#include <vector> // this is needed to use the vector library
#include <string>

template <typename someType>
void printMyVector(std::vector <someType> newVector) {
    for (unsigned int i = 0; i < newVector.size() ; i++) {
        std::cout << "Index: " << i << " has a value of " << newVector[i] << "." << std::endl;
    }
}

int main() {
    
    std::vector <std::string> stringVector;
    std::vector <int> intVector;
    
    // assign members truncates the vector and adds the value
    stringVector.assign(5, "Hello World");
    printMyVector(stringVector);
    
    std::cout << "--------------------------------------------------" << std::endl;
    
    stringVector.assign(3, "Goodbye World");
    printMyVector(stringVector);
    
    std::cout << "--------------------------------------------------" << std::endl;
    
    
    // insert a value at the end of the vector
    stringVector.insert(stringVector.end(), "Hello World");
    printMyVector(stringVector);
    
    std::cout << "--------------------------------------------------" << std::endl;
    
    // swap function swaps the value given within vector
    std::swap(stringVector[0], stringVector[3]);
    printMyVector(stringVector);
    
    std::cout << "--------------------------------------------------" << std::endl;
    
    
    return 0;
}
