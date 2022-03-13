#ifndef PROIECT_BOARD_H
#define PROIECT_BOARD_H

#include <iostream>
#include <string>

using namespace std;

class Board {
public:
    char ** board; // board[8][8]

    Board();

    ~Board();

    void set_default_board(char board[8][8]);

    void print_board();

/*    void update_board(string move);*/

    void mirror();

};


#endif //PROIECT_BOARD_H
