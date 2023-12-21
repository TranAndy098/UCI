#include <iostream>

class Student {
public:
    static int studentCounter;
    Student() {std::cout << "Inside Constuctor" << std::endl;};
    ~Student() {std::cout << "Inside Deconstuctor" << std::endl;};
};

int counterFunction() {
    // static variable declaration
    static int counter = 0; // without static it would reset, but with static it will remeber the change
    
    // incremnet our static variable
    return counter++;
    
}

int Student::studentCounter = 1;

int main() {
    
    for (int i = 0; i < 5; i++) {
        std::cout << counterFunction() << std::endl;
    }
    
    Student student1;
    Student student2;
    student1.studentCounter = 10;
    std::cout << student1.studentCounter << std::endl;
    student2.studentCounter = 100;
    std::cout << student1.studentCounter << std::endl; // even thoguht we changed studentCounter for student2 it changes for all objects of the Student class because it is a static variable meaning it is universal
    
    int temp = 0;
    if (temp == 0) {Student obj;} // the current Student obj only exists in the if statement so it is constructed and deconstructed in it but if it is a static Student obj then it is cosntucted here but deconstructed at the end because its life isnt only in the if statement
    
    std::cout << "End of program" << std::endl;
    
    return 0;
}
