#include "Board.h"

Board::Board() {
    board = new char*[8];
    for (int i = 0; i < 8; i++) {
        board[i] = new char[8];
    }
}

Board::~Board() {
    delete[] board;
}

void Board::set_default_board(char (*board)[8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            this->board[i][j] = board[i][j];
        }
    }
}

void Board::print_board() {
    for (int i = 0; i < 8; i++) {
        cout << "[";
        for (int j = 0; j < 8; j++) {
            cout << board[i][j] << " ";
        }
        cout << "]" << endl;
    }
}

/*void Board::update_board(string move) {
    if (Engine::white) {
        Engine::make_move_opp(this->board, AI::convert_move_white(move),"");
    } else {
        Engine::make_move_opp(this->board, AI::convert_move(move), "");
    }
}*/

void Board::mirror() {
    char aux;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            if (islower(this->board[i][j])) {
                aux = toupper(this->board[i][j]);
            } else {
                aux = tolower(this->board[i][j]);
            }
            if (islower(this->board[7 - i][7 - j])) {
                this->board[i][j] = toupper(this->board[7 - i][7 - j]);
            } else {
                this->board[i][j] = tolower(this->board[7 - i][7 - j]);
            }
            this->board[7 - i][7 - j] = aux;

        }
    }
}

