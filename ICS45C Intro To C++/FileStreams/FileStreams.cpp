// including the input output stream (defaulting to console)
#include <iostream>

//this is a file stream does both in and out from files
#include <fstream>

// this is a library stream that allows input of stream of data from files
#include <istream>

// this is a standard library stream thatt allows output streams to files
#include <ostream>

#include <string>

// function that uses the istreama nd ostream classses
void seperateStreamForIO(std::string fileContent) {
    std::string fileLine = "";
    std::ifstream myInputFStream;
    std::ofstream myOutputStream;
    
    std::cout << "My file contains the following:\n" << fileContent;
    myInputFStream.open("myNewFile.txt");
    if (myInputFStream) { // myInputFStream.is_open() can also be used instead of myInputFStream
        getline(myInputFStream,fileLine);
        std::cout << "Existing File Content" << std::endl;
        std::cout<< fileLine << std::endl;
    }
    else {
        std::cout << "The file you tried to open doesn't exists or failed to open, opening one that does exists." << std::endl;
        myInputFStream.open("myFirstFile.txt");
        std::cout << "Did my file open: " << myInputFStream.is_open() << std::endl;
        myOutputStream.open("myNewFile.txt");
        
        while (!myInputFStream.eof()) {
            getline(myInputFStream,fileLine);
            if (fileLine != "") {
                std::cout << "Line being read: " << fileLine << std::endl;
                myOutputStream << fileLine << std::endl;
            }
        }
    }
    
}

// using the filestream object
std::string usingGeneralFilestream(){
    std::fstream myFStreamFile;
    std::string filename = "myFirstFile.txt";
    std::string inputLine = "";
    std::string returnString = "";
    
    myFStreamFile.open(filename,std::ios::out | std::ios::in | std::ios::trunc); // you can only have std::ios::app or std::ios::trunc at a time, none but never both. output needs to be first so that it can get created
    
    for (int i = 0; i < 10; i++) {
        myFStreamFile << "This is line number " << std::to_string(i+1) << "." << std::endl;
        std::cout << "This is line number " << std::to_string(i+1) << "." << std::endl;
    }
    
    myFStreamFile.seekg(0);
    
    for (int i = 0; i < 10; i++) {
        std::cout << "Line " << std::to_string(i+1) << " - ";
        getline(myFStreamFile,inputLine);
        std::cout << inputLine << std::endl;
        returnString += inputLine + "\n";
    }
    
    myFStreamFile.close();
    
    return returnString;
}

// call our different file associated functions
int main() {
    
    std::string FileContent = "";
    
    FileContent = usingGeneralFilestream();
    
    seperateStreamForIO(FileContent);
    
    return 0;
}
