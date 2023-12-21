#include "Functions.h"
#include <fstream>
#include <iostream>


void add(std::string a, std::string b, std::string output) {
    std::string inputLine = "";
    std::string n = "";
    int c = 0;
    int r = 0;
    std::string prev = "";

    std::ifstream myInputFStream;
    std::ofstream myOutputStream;
    
    myInputFStream.open(a);
    while (!myInputFStream.eof()) {
            getline(myInputFStream,inputLine);
            if (inputLine != "") {
                r += 1;
                int cc = 1;
                for (int o = 0; o < inputLine.size(); o++){
                    if (inputLine.at(o) == ' ') {
                        cc += 1;
                        }
                    }
                c = cc;

            }
    }
    
    myInputFStream.close();
    
    int am[r][c];
    
    myInputFStream.open(a);
    int cr = 0;
    int cc = 0;
    while (!myInputFStream.eof()) {
        getline(myInputFStream,inputLine);
        if (inputLine != "") {
        //std::cout << inputLine << std::endl;
            for (int o = 0; o < inputLine.size(); o++){
                if (inputLine.at(o) == ' ') {
                    am[cr][cc] = stoi(n);
                    n = "";
                    cc += 1;
                }
                else {
                    n += inputLine.at(o);
                }
            }
        am[cr][cc] = stoi(n);
        n = "";
        cc = 0;
        }
        else {
            break;
        }
        cr += 1;
    }
    
    myInputFStream.close();
    
    myInputFStream.open(b);
    int bm[r][c];
    cr = 0;
    cc = 0;
    while (!myInputFStream.eof()) {
        getline(myInputFStream,inputLine);
        if (inputLine != "") {
        //std::cout << inputLine << std::endl;
            for (int o = 0; o < inputLine.size(); o++){
                if (inputLine.at(o) == ' ') {
                    bm[cr][cc] = stoi(n);
                    n = "";
                    cc += 1;
                }
                else {
                    n += inputLine.at(o);
                }
            }
        bm[cr][cc] = stoi(n);
        n = "";
        cc = 0;
        }
        else {
            break;
        }
        cr += 1;
    }
    
    myInputFStream.close();
    
    myOutputStream.open(output);
    
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            int ca = 0;
            ca = am[i][j] + bm[i][j];
            if (j + 1 == c){
                if (i + 1 == r){
                    myOutputStream << ca;
                }
                else {
                    myOutputStream << ca << std::endl;
                }
            }
            else {
                myOutputStream << ca << " ";
            }
        }
    }
    myOutputStream.close();
    
}


void sub(std::string a, std::string b, std::string output) {
    std::string inputLine = "";
    std::string n = "";
    int c = 0;
    int r = 0;
    std::string prev = "";

    std::ifstream myInputFStream;
    std::ofstream myOutputStream;
    
    myInputFStream.open(a);
    while (!myInputFStream.eof()) {
            getline(myInputFStream,inputLine);
            if (inputLine != "") {
                r += 1;
                int cc = 1;
                for (int o = 0; o < inputLine.size(); o++){
                    if (inputLine.at(o) == ' ') {
                        cc += 1;
                        }
                    }
                c = cc;

            }
    }
    
    myInputFStream.close();
    
    int am[r][c];
    
    myInputFStream.open(a);
    int cr = 0;
    int cc = 0;
    while (!myInputFStream.eof()) {
        getline(myInputFStream,inputLine);
        if (inputLine != "") {
        //std::cout << inputLine << std::endl;
            for (int o = 0; o < inputLine.size(); o++){
                if (inputLine.at(o) == ' ') {
                    am[cr][cc] = stoi(n);
                    n = "";
                    cc += 1;
                }
                else {
                    n += inputLine.at(o);
                }
            }
        am[cr][cc] = stoi(n);
        n = "";
        cc = 0;
        }
        else {
            break;
        }
        cr += 1;
    }
    
    myInputFStream.close();
    
    myInputFStream.open(b);
    int bm[r][c];
    cr = 0;
    cc = 0;
    while (!myInputFStream.eof()) {
        getline(myInputFStream,inputLine);
        if (inputLine != "") {
        //std::cout << inputLine << std::endl;
            for (int o = 0; o < inputLine.size(); o++){
                if (inputLine.at(o) == ' ') {
                    bm[cr][cc] = stoi(n);
                    n = "";
                    cc += 1;
                }
                else {
                    n += inputLine.at(o);
                }
            }
        bm[cr][cc] = stoi(n);
        n = "";
        cc = 0;
        }
        else {
            break;
        }
        cr += 1;
    }
    
    myInputFStream.close();
    
    myOutputStream.open(output);
    
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            int ca = 0;
            ca = am[i][j] - bm[i][j];
            if (j + 1 == c){
                if (i + 1 == r){
                    myOutputStream << ca;
                }
                else {
                    myOutputStream << ca << std::endl;
                }
            }
            else {
                myOutputStream << ca << " ";
            }
        }
    }
    myOutputStream.close();
    
}
void mul(std::string a, std::string b, std::string output) {
    std::string inputLine = "";
    std::string n = "";
    int ac = 0;
    int ar = 0;
    std::string prev = "";

    std::ifstream myInputFStream;
    std::ofstream myOutputStream;
    
    myInputFStream.open(a);
    while (!myInputFStream.eof()) {
            getline(myInputFStream,inputLine);
            if (inputLine != "") {
                ar += 1;
                int cc = 1;
                for (int o = 0; o < inputLine.size(); o++){
                    if (inputLine.at(o) == ' ') {
                        cc += 1;
                        }
                    }
                ac = cc;

            }
    }
    
    myInputFStream.close();
    
    int am[ar][ac];
    
    myInputFStream.open(a);
    int cr = 0;
    int cc = 0;
    while (!myInputFStream.eof()) {
        getline(myInputFStream,inputLine);
        if (inputLine != "") {
        //std::cout << inputLine << std::endl;
            for (int o = 0; o < inputLine.size(); o++){
                if (inputLine.at(o) == ' ') {
                    am[cr][cc] = stoi(n);
                    n = "";
                    cc += 1;
                }
                else {
                    n += inputLine.at(o);
                }
            }
        am[cr][cc] = stoi(n);
        n = "";
        cc = 0;
        }
        else {
            break;
        }
        cr += 1;
    }
    
    myInputFStream.close();
    
    int bc = 0;
    int br = 0;
    
    myInputFStream.open(b);
    while (!myInputFStream.eof()) {
            getline(myInputFStream,inputLine);
            if (inputLine != "") {
                br += 1;
                int cc = 1;
                for (int o = 0; o < inputLine.size(); o++){
                    if (inputLine.at(o) == ' ') {
                        cc += 1;
                        }
                    }
                bc = cc;
            }
    }
    
    myInputFStream.close();
    
    myInputFStream.open(b);
    int bm[br][bc];
    cr = 0;
    cc = 0;
    while (!myInputFStream.eof()) {
        getline(myInputFStream,inputLine);
        if (inputLine != "") {
        //std::cout << inputLine << std::endl;
            for (int o = 0; o < inputLine.size(); o++){
                if (inputLine.at(o) == ' ') {
                    bm[cr][cc] = stoi(n);
                    n = "";
                    cc += 1;
                }
                else {
                    n += inputLine.at(o);
                }
            }
        bm[cr][cc] = stoi(n);
        n = "";
        cc = 0;
        }
        else {
            break;
        }
        cr += 1;
    }
    
    myInputFStream.close();
    
    myOutputStream.open(output);
    for (int i = 0; i < ar; i++){
            for (int j = 0; j < bc; j++){
                int ca = 0;
                for (int fc = 0; fc < ac; fc++){
                    ca += am[i][fc] * bm[fc][j];
                }
                if (j + 1 == bc){
                    if (i + 1 == ar){
                        myOutputStream << ca;
                    }
                    else {
                        myOutputStream << ca << std::endl;
                    }
                }
                else {
                    myOutputStream << ca << " ";
                }
            }

    }
    
    myOutputStream.close();
    
}
