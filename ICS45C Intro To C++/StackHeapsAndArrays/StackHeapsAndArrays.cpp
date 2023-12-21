#include <iostream>

// this function passes an array and size to fill the aray with data
void fillMyArray(int arrayToFill[], int sizeOfArray) {
    for (int i = 0; i < sizeOfArray; i++){
        arrayToFill[i] = i;
    }
}

// this function iterated through an array to print its contents
void printMyArray(int arrayToFill[], int sizeOfArray) {
    for (int i = 0; i < sizeOfArray; i++){
        std::cout << "Array Value at (i=" << i << "): " << arrayToFill[i] << " at memory lcoation: " << &arrayToFill[i] << std::endl;
    }
}

// this function passes an array and size to fill the aray with data
void fillMy2DArray(int arrayToFill[][10], int sizeOfArray) {
    for (int i = 0; i < sizeOfArray; i++){
        for (int j = 0; j < sizeOfArray; j++){
            arrayToFill[i][j] = (i * 10) + j;
        }
    }
}

// this function iterated through an array to print its contents
void printMy2DArray(int arrayToFill[][10], int sizeOfArray) {
    for (int i = 0; i < sizeOfArray; i++){
        for (int j = 0; j < sizeOfArray; j++){
            std::cout << "Array Value at (i=" << i << ") and (j=" << j << "): " << arrayToFill[i][j] << " at memory lcoation: " << &arrayToFill[i][j] << std::endl;
        }    }
}

int main() {
    
    int sizeOfMyArray = 10; // int variable will be used to hold the array size
    int oneDimArray1[10]; // declaring a one dimensional array fo size 10
    int oneDimArray2[10]; // we can not use the sizeOfMyArray as the integer because it does not know the sizeOfMyArray at compile time since this is static allocation
    int * oneDimDymArray1 = new int[10]; // declaring a one dimension dynamic array by creating a pointer to the first memory location
    int * oneDimDymArray2 = new int[sizeOfMyArray]; // we can use the sizeOfMyArray as the integer because it does know the sizeOfMyArray at run time since this is dynamic allocation
    int twoDimArray[10][10]; // decalaring a 2-D array
    
    
    // passing static arrays
    std::cout << "Static Arrays" << std::endl;
    
    std::cout << "Array 1" << std::endl;
    fillMyArray(oneDimArray1,sizeOfMyArray);
    printMyArray(oneDimArray1,sizeOfMyArray);
    
    std::cout << "\n" << "Array 2" << std::endl;
    fillMyArray(oneDimArray2,sizeOfMyArray);
    printMyArray(oneDimArray2,sizeOfMyArray);
    
    // passing dynamic arrrays
    std::cout << "\n" << "Dynamic Arrays" << std::endl;
    
    std::cout << "Array 1" << std::endl;
    fillMyArray(oneDimDymArray1,sizeOfMyArray);
    printMyArray(oneDimDymArray1,sizeOfMyArray);
    
    std::cout << "\n" << "Array 2" << std::endl;
    fillMyArray(oneDimDymArray2,sizeOfMyArray);
    printMyArray(oneDimDymArray2,sizeOfMyArray);
    
    // passing 2-D arrays
    std::cout << "\n" << "2-D Arrays" << std::endl;
    
    std::cout << "Array 1" << std::endl;
    fillMy2DArray(twoDimArray,sizeOfMyArray);
    printMy2DArray(twoDimArray,sizeOfMyArray);

    // deallocating dynamic memory for clean up
    delete [] oneDimDymArray1; // not having the [] will only deallocate the pointer but not the array
    delete [] oneDimDymArray2;
    
    return 0;
}
