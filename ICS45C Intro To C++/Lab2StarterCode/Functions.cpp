#include "Functions.h"

void runGame()
{
    bool games = true;
    while (games == true) {
    char piece = 'X';
    bool game = true;
    char board[3][3];
    initBoard(board);
    while (game == true) {
        bool move = false;
        int x = 0;
        int y = 0;
        while (move == false){
            string xy;
            std::cout <<  "Enter coordinate for " << piece << ". Input should be X Y" << std::endl;
            
            /*getline (cin, xy);
             */
            /*
            if (xy.empty()) {
                getline (cin, xy);
            }
             */
            /*
            x = xy[0] - '0';
            y = xy[2] - '0';
            */
            cin >> x;
            cin >> y;
            if (board[x][y] == '-'){
                if (y < 3 && x < 3){
                move = true;
                }
            }
        }
        placeAPiece(x,y,piece,board);
        displayBoard(board);
        if (checkForWinner(piece,board) == true) {
            std::cout << piece << " Won" << std::endl;
            game = false;
        }
        else if (checkForDraw(board) == true) {
            std::cout <<  "Draw" << std::endl;
            game = false;
        }
        
        if (piece == 'X') {
            piece = 'O';
        }
        else {
            piece = 'X';
        }
    }
        std::cout <<  "Do you want to play again?" << std::endl;
        string cont;
        /*
        getline (cin, cont);
        */
        cin >> cont;
        bool cor = false;
        if (cont == "n" || cont == "N") {
            cor = true;
        }
        if (cont == "y" || cont == "Y") {
            cor = true;
        }
        while (cor == false) {
            std::cout <<  "Do you want to play again?" << std::endl;
            cin >> cont;
            if (cont == "n" || cont == "N") {
                cor = true;
            }
            if (cont == "y" || cont == "Y") {
                cor = true;
            }
        }
        if (cont == "n" || cont == "N") {
            games = false;
        }
        if (cont == "y" || cont == "Y") {
            games = true;
        }
    }
    std::cout <<  "Done" << std::endl;
}

void initBoard(char board[3][3])
{
    board[0][0] = '-';
    board[0][1] = '-';
    board[0][2] = '-';
    board[1][0] = '-';
    board[1][1] = '-';
    board[1][2] = '-';
    board[2][0] = '-';
    board[2][1] = '-';
    board[2][2] = '-';
}

void placeAPiece(int x, int y, char piece, char board[3][3])
{
    board[x][y] = piece;
}

bool checkForWinner(char piece, char board[3][3])
{
    if (board[0][0] == piece) {
        if (board[0][1] == piece) {
            if (board[0][2] == piece) {
                return true;
            }
        }
        if (board[1][1] == piece) {
            if (board[2][2] == piece) {
                return true;
            }
        }
        if (board[1][0] == piece) {
            if (board[2][0] == piece) {
                return true;
            }
        }
    }
    if (board[0][1] == piece) {
        if (board[1][1] == piece) {
            if (board[2][1] == piece) {
                return true;
            }
        }
    }
    if (board[0][2] == piece) {
        if (board[1][1] == piece) {
            if (board[2][0] == piece) {
                return true;
            }
        }
        if (board[1][2] == piece) {
            if (board[2][2] == piece) {
                return true;
            }
        }
    }
    if (board[1][0] == piece) {
        if (board[1][1] == piece) {
            if (board[1][2] == piece) {
                return true;
            }
        }
    }
    if (board[2][0] == piece) {
        if (board[2][1] == piece) {
            if (board[2][2] == piece) {
                return true;
            }
        }
    }
    return false;
}

bool checkForDraw(char board[3][3])
{
    int empty = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '-') {
                ++empty;
            }
            }
        }
    if (empty == 0) {
        if (checkForWinner('X',board) == false) {
        return true;
        }
        else if (checkForWinner('O',board) == false) {
            return true;
            }
            else {
                return false;
            }
    }
    else {
        return false;
    }
}


void displayBoard(char board[3][3])
{
    /*
    for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (j == 2) {
                    std::cout <<  board[i][j] << std::endl;
                }
                else {
                    std::cout << board[i][j] << '|';
                }
                }
            if (i < 2) {
                std::cout <<  "-----" << std::endl;
            }
            }
   */
/*
    string s;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (j == 2) {
                string p = "-";
                if (board[i][j] == 'X') {
                    p = "X";
                }
                if (board[i][j] == 'O') {
                    p = "O";
                }
                s = s + p;
            }
            else {
                string p = "-";
                if (board[i][j] == 'X') {
                    p = "X";
                }
                if (board[i][j] == 'O') {
                    p = "O";
                }
                s = s + p + "|";
            }
            }
        if (i < 2) {
            s = s + "\n" + "-----" + "\n";
        }
        }
    std::cout << s << std::endl;
*/


    std::cout << board[0][0] << '|' << board[0][1] << '|' << board[0][2] << std::endl;
    std::cout << "-----" << std::endl;
    std::cout << board[1][0] << '|' << board[1][1] << '|' << board[1][2] << std::endl;
    std::cout << "-----" << std::endl;
    std::cout << board[2][0] << '|' << board[2][1] << '|' << board[2][2] << std::endl;

}
