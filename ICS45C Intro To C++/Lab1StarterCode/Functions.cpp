#include "Functions.h"

string createPyramid(int num)
{
    int dash = 1;
    std::string space;
    std::string dashes;
    std::string bar;
    space = " ";
    dashes = "-";
    bar = "|";
    if (0 < num) {
        if (500 > num) {
            std::string s;
            while (num > 0) {
                for (int i = 0; i < num; i++) {
                    s = s + space;
                    }
                for (int i = 0; i < dash; i++) {
                    s = s + dashes;
                    }
                s = s + "\n";
                num = num - 1;
                dash = dash + 2;
                for (int i = 0; i < num; i++) {
                    s = s + space;
                    }
                for (int i = 0; i < dash; i++) {
                    if (i % 2 == 0) {
                        s = s + bar;
                    }
                    else {
                        s = s + space;
                    }
                    }
                s = s + "\n";
                
                
            }
            s = s + " ";
            for (int i = 0; i < dash-2; i++) {
                s = s + dashes;
                }
            return s;
        }
        else {
            return "Pyramid size too large.";
        }
    }
    else if (num == 0) {
        return "Invalid pyramid size.";
    }
    else {
        return "Negative pyramid size.";
    }
}

int getUserInput()
{
    std::cout <<  "Enter a number between 0 and 500:" << std::endl;
    int num;
    cin >> num;
    return num;
}
