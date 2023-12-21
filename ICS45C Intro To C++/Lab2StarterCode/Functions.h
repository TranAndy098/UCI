#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <iostream>
#include <string>

using namespace std;

void runGame();
void initBoard(char[3][3]);
void placeAPiece(int, int, char, char[3][3]);
bool checkForWinner(char, char[3][3]);
bool checkForDraw(char[3][3]);
void displayBoard(char[3][3]);

#endif /* FUNCTIONS_H_ */