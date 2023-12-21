#include <iostream>

// Below is defining each type function seperately
/*
void dataSwap(int &dataValue1, int &dataValue2) {
    int tempDataValue = dataValue1;
    dataValue1 = dataValue2;
    dataValue2 = tempDataValue;
    
    std::cout << "Now, Data Value 1 is " << dataValue1 << " and Data Value 2 is " << dataValue2 << std::endl;
}

void dataSwap(char &dataValue1, char &dataValue2) {
    char tempDataValue = dataValue1;
    dataValue1 = dataValue2;
    dataValue2 = tempDataValue;
    
    std::cout << "Now, Char Value 1 is " << dataValue1 << " and Char Value 2 is " << dataValue2 << std::endl;
}
*/

// template function
template <typename dVal>
void dataSwap(dVal &dataValue1, dVal &dataValue2, int someVal = 0) { // someValue is just a default value to show that not al types have to be of dVal
    dVal tempDataValue = dataValue1;
    dataValue1 = dataValue2;
    dataValue2 = tempDataValue;
    
    std::cout << "Now, Data Value 1 is " << dataValue1 << " and Data Value 2 is " << dataValue2 << std::endl;
}

template <typename dVal1, typename dVal2> class TemplateClass {
public:
    dVal1 val1;
    dVal2 val2;
    int counter = 0;
    void dataSwap(dVal1 &dataValue1, dVal2 &dataValue2, int someVal = 0) { // someValue is just a default value to show that not al types have to be of dVal
        dVal1 tempDataValue = dataValue1;
        dataValue1 = dataValue2;
        dataValue2 = tempDataValue;
        
        std::cout << "Now Class, Data Value 1 is " << dataValue1 << " and Data Value 2 is " << dataValue2 << std::endl;
    }
    
};

int main() {
   
    int dataValue1 = 50, dataValue2 = 100;
    dataSwap(dataValue1,dataValue2);
    
    char charValue1 = '?', charValue2 = '!';
    dataSwap(charValue1,charValue2);
    
    std::string strValue1 = "abd", strValue2 = "def";
    dataSwap(strValue1,strValue2);
    
    TemplateClass<int, int> tc1;
    TemplateClass<std::string, std::string> tc2;
    
    tc1.dataSwap(dataValue1, dataValue2);
    tc2.dataSwap(strValue1, strValue2);
    
    return 0;
}
