#include <iostream>
#include <cstring>
/* char <variable name> [size of character array]
 strcpy(s1,s2); - copies s2 into s1
 strcat(s1,s2); - concatenates s2 at the end of s1
 strlen(s1); - length of s1
 strcmp(s1,s2); - 0 if equal, less than 0 if s1<s2, greater than 0 if s1 > s2
 strchr(s1,ch); - returns a pointer to the first occurance of ch in s1
 strstr(s1,s2); - returns a pointer to the first occurance of s2 in s1
 sometimes you can only use cstring and not string and that is when you would use cstring
 */
#include <string>
/* string <variable name>
 mostly use strings compared to cstrings
 use c_str() to treat a string into a cstring
 to access a index use string.at(X) rather then string[X]  where X is the index
 String s1(s2); - copies s2 into s1
 s1 + s2; - concatenates s2 at the end of s1
 s1.size(); - length of s1
 s1.compare(s2); - 0 if equal, less than 0 if s1<s2, greater than 0 if s1 > s2
 s1.find_first_of(ch); - returns a pointer to the first occurance of ch in s1
 s1.find(s2); - returns a pointer to the first occurance of s2 in s1
 don't risk overflow
 better for dynamic strings
 */
int main() {
    
    // String example of defining new string and appending
    std::string helloworld = "Hello World!"; // defines a new helloworld string
    // must use std:: in front of string
    helloworld += "\n";
    std::cout << helloworld; // << std::endl;
    
    //-------------------------
    
    // Example of using strings in if statements
    std::string classname = "ICS 45"; // defining a new string to store class name
    classname += "C"; // append C to make it ICS 45C
    std::string classnamev2 = "ICS 45C";
    // if statemnt comparing string
    if (classname == "ICS 45C"){
        std::cout << "Same Class" << std::endl;
    }
    else {
        std::cout << "Different Class" << std::endl;
    }
    if (classname == classnamev2){
        std::cout << "v1 is same as v2" << std::endl;
    }
    else {
        std::cout << "v1 is different than v2" << std::endl;
    }
    std::cout << "First print: " << classname.compare(classnamev2) << std::endl; // compares the same length (0)
    classnamev2 += "\n";
    std::cout << "Second print: " << classname.compare(classnamev2) << std::endl; // compares where v2 is longer (-1 or less than 0)
    classnamev2 = "Hello";
    std::cout << "Third print: " << classname.compare(classnamev2) << std::endl; // compares where v2 is shoprter (1 or greater than 0)
    
    //-------------------------
    
    // Printing the sizes of strings and using index
    std::cout << "Version 1 size of \"" << classname << "\" : "<< classname.size() << std::endl;
    std::cout << "Version 2 size of \"" << classnamev2 << "\" : "<< classnamev2.size() << std::endl;
    
    // indexing with string[X]
    for (int i = 0; i < classname.size(); i++) {
        std::cout << classname[i] << " ";
    }
    std::cout << std::endl;
    
    // indexing with string.at(X)
    for (int i = 0; i < classname.size(); i++) {
        std::cout << classname.at(i) << " ";
    }
    std::cout << std::endl;
    
    //-------------------------
    
    // Demonstration of mutability
    // in Python and Java strings are immutable so when we change the string it uses a different memory to store it and in C++ strings are mutable so changing it copies the original and adds it to the string in the same memory
    std::string greeting = "Hello";
    std::cout << "Original Greeting memory location: " << &greeting << std::endl;
    greeting += " World!";
    std::cout << "Changed Greeting memory location: " << &greeting << std::endl;
    
    //-------------------------
    
    // Demostration of boundraies in C++
    // index with string[X]
    std::cout << greeting.size() << std::endl;
    std::cout << "-1st Character of \"" << greeting << "\" : " << greeting[-1] << std::endl; // C++ allows us to print an out of bounds index but in this case prints nothing becasue memory is empty but if it was not then it could print something random
    std::cout << "12th Character of \"" << greeting << "\" : " << greeting[11] << std::endl;
    std::cout << "13th Character of \"" << greeting << "\" : " << greeting[12] << std::endl; // C++ allows us to print an out of bounds index but in this case prints nothing becasue memory is empty but if it was not then it could print something random
    
    // index with string.at(X)
    //std::cout << "-1st Character of \"" << greeting << "\" : " << greeting.at(-1) << std::endl; // string.at(X) when x is out of bound, will throw an exception like Python and terminate
    std::cout << "12th Character of \"" << greeting << "\" : " << greeting.at(11) << std::endl;
    //std::cout << "13th Character of \"" << greeting << "\" : " << greeting.at(12) << std::endl; // string.at(X) when x is out of bound, will throw an exception like Python and terminate
    
    
    
    
    
    return 0;
}
