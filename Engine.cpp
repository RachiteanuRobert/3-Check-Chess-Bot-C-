#include "Engine.h"

bool Engine::white;
bool Engine::running;

Engine::Engine() {}

Engine::~Engine() {}

void Engine::make_move(char **chess_board, string move, string last_move) {
    if (move[4] != 'P') {
        int i_l = move[0] - '0', i_c = move[1] - '0', f_l = move[2] - '0',
        f_c = move[3] - '0';
        int l_i_l = last_move[0] - '0', l_i_c = last_move[1] - '0', l_f_l = last_move[2] - '0',
        l_f_c = last_move[3] - '0';
        if (chess_board[i_l][i_c] == 'P' && chess_board[l_f_l][l_f_c] == 'p' &&
        i_l == 4 && f_l == 5) { // en passant
            chess_board[l_f_l][l_f_c] = ' ';
        }
        if (move[0] == '0' && move[1] == '4' && move[2] == '0' && move[3] == '2' &&
        chess_board[0][4] == 'G') {
            chess_board[0][0] = ' ';
            chess_board[0][3] = 'R';
        }
        if (move[0] == '0' && move[1] == '4' && move[2] == '0' && move[3] == '6' &&
            chess_board[0][4] == 'G') {
            chess_board[0][7] = ' ';
            chess_board[0][5] = 'R';

        }
        chess_board[f_l][f_c] = chess_board[i_l][i_c];
        chess_board[i_l][i_c] = ' ';
    } else { // i_c f_c c promotion P
        int i_l = 6, i_c = move[0] - '0', f_l = 7, f_c = move[1] - '0';
        chess_board[f_l][f_c] = move[3];
        chess_board[i_l][i_c] = ' ';
    }
}

void Engine::make_move_opp(char **chess_board, string move, string last_move) {
    int i_l = move[0] - '0', i_c = move[1] - '0', f_l = move[2] - '0',
    f_c = move[3] - '0';
    int l_i_l = last_move[0] - '0', l_i_c = last_move[1] - '0', l_f_l = last_move[2] - '0',
    l_f_c = last_move[3] - '0';
    if (move[4] == 'q' && move[2] == '0' && move[0] == '1') {
        chess_board[f_l][f_c] = move[4];
        chess_board[i_l][i_c] = ' ';
    } else {
        if (chess_board[i_l][i_c] == 'p' && chess_board[l_f_l][l_f_c] == 'P' &&
            i_l == 3 && l_i_l == 1) { // en passant
            chess_board[l_f_l][l_f_c] = ' ';
        }
        if (move[0] == '7' && move[1] == '4' && move[2] == '7' && move[3] == '2' &&
            chess_board[7][4] == 'g') {
            chess_board[7][0] = ' ';
            chess_board[7][3] = 'r';
        }
        if (move[0] == '7' && move[1] == '4' && move[2] == '7' && move[3] == '6' &&
            chess_board[7][4] == 'g') {
            chess_board[7][7] = ' ';
            chess_board[7][5] = 'r';

        }
        if (move[0] == '0' && move[1] == '4' && move[2] == '0' && move[3] == '2' &&
            chess_board[0][4] == 'G') {
            chess_board[0][0] = ' ';
            chess_board[0][3] = 'R';
        }
        if (move[0] == '0' && move[1] == '4' && move[2] == '0' && move[3] == '6' &&
            chess_board[0][4] == 'G') {
            chess_board[0][7] = ' ';
            chess_board[0][5] = 'R';

        }
        chess_board[f_l][f_c] = chess_board[i_l][i_c];
        chess_board[i_l][i_c] = ' ';
    }
}

void Engine::set_white(bool value) {
    white = value;
}

void Engine::set_running(bool value) {
    running = value;
}

