#include "AI.h"

int AI::row_G;

int AI::column_G;

bool AI::king_moved;

bool AI::l_rook_moved;

bool AI::r_rook_moved;

AI::AI() {}

AI::~AI() {}

string AI::convert_move(string move) {
    string converted_move;
    char i_l = '8' - move[1] + '0' , i_c = move[0] - '1',
            f_l = '8' - move[3] + '0', f_c = move[2] - '1';
    char promotion;
    if (move[4] == 'q') { // Pawn promotion case
        promotion = move[4];
    } else {
        promotion = ' ';
    }
    converted_move += i_l;
    converted_move += i_c;
    converted_move += f_l;
    converted_move += f_c;
    converted_move += promotion;
    return converted_move;
}

string AI::unconvert_move(string move) {
    string unconverted_move;
    char i_l = move[1] + '1', i_c = '8' - move[0] + '0',
            f_l = move[3] + '1', f_c = '8' - move[2] + '0';
    char promotion = ' ';
    if (move[4] == 'P') { // Pawn promotion case
        i_l = move[0] + '1';
        i_c = '2';
        f_l = move[1] + '1';
        f_c = '1';
        promotion = tolower(move[3]);
    }
    unconverted_move += i_l;
    unconverted_move += i_c;
    unconverted_move += f_l;
    unconverted_move += f_c;
    unconverted_move += promotion;
    return unconverted_move;
}

string AI::convert_move_white(string move) {
    string converted_move;
    char i_l = move[1] - 1, i_c = move[0] - 42 - 2 * (move[0] - 'a'),
            f_l = move[3] - 1, f_c = move[2] - 42 - 2 * (move[2] - 'a');
    char promotion;
    if (move[4] == 'q') { // Pawn promotion case
        promotion = move[4];
    } else {
        promotion = ' ';
    }
    converted_move += i_l;
    converted_move += i_c;
    converted_move += f_l;
    converted_move += f_c;
    converted_move += promotion;
    return converted_move;
}

string AI::unconvert_move_white(string move) {
    string unconverted_move;
    char i_l = move[1] + 42 + 2 * ('7' - move[1]), i_c = move[0] + 1,
            f_l = move[3] + 42 + 2 * ('7' - move[3]), f_c = move[2] + 1;
    char promotion = ' ';
    if (move[4] == 'P') { // Pawn promotion case
        i_l = move[0] + 42 + 2 * ('7' - move[0]);
        i_c = '7';
        f_l = move[1] + 42 + 2 * ('7' - move[1]);
        f_c = '8';
        promotion = tolower(move[3]);
    }
    unconverted_move += i_l;
    unconverted_move += i_c;
    unconverted_move += f_l;
    unconverted_move += f_c;
    unconverted_move += promotion;
    return unconverted_move;

}

/*
{'R','K','B','Q','G','B','K','R'}, // BIG LETTER -> Black; small letter -> White;
{'P','P','P','P','P','P','P','P'}, // R/r -> Rook(turn)
{' ',' ',' ',' ',' ',' ',' ',' '}, // K/k -> Knight(cal)
{' ',' ',' ',' ',' ',' ',' ',' '}, // B/b -> Bishop(nebun)
{' ',' ',' ',' ',' ',' ',' ',' '}, // Q/q -> Queen(regina)
{' ',' ',' ',' ',' ',' ',' ',' '}, // G/g -> King(rege)
{'p','p','p','p','p','p','p','p'}, // P/p -> Pawn(pion)
{'r','k','b','q','g','b','k','r'}
};*/

bool AI::check_in_bounds(int i, int j){
    bool ok = false;
    if((i >= 0) && (i <=7) && (j >= 0) && (j <= 7))
        ok = true;

    return ok;
}
vector<string> AI::get_possible_moves(char **board) {
    AI::king_moved = false;
    AI::l_rook_moved = false;
    AI::r_rook_moved = false;
    vector<string> moves;
    vector<string> aux_moves;

    int i_k, j_k;
    for(i_k = 0; i_k < 8; i_k++) {
        for (j_k = 0; j_k < 8; j_k++) {
            if(board[i_k][j_k] == 'G') {
                goto end_of_loops;
            }
        }
    }
    end_of_loops:

    AI::row_G = i_k;
    AI::column_G = j_k;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == 'P') {
                aux_moves = get_possible_moves_pawn(i, j, board);
                moves.insert(moves.end(), aux_moves.begin(), aux_moves.end());
            }
            if (board[i][j] == 'R') {
                aux_moves = get_possible_moves_rook(i, j, board);
                moves.insert(moves.end(), aux_moves.begin(), aux_moves.end());
            }
            if (board[i][j] == 'K') {
                aux_moves = get_possible_moves_knight(i, j, board);
                moves.insert(moves.end(), aux_moves.begin(), aux_moves.end());
            }
            if (board[i][j] == 'B') {
                aux_moves = get_possible_moves_bishop(i, j, board);
                moves.insert(moves.end(), aux_moves.begin(), aux_moves.end());
            }
            if (board[i][j] == 'Q') {
                aux_moves = get_possible_moves_queen(i, j, board);
                moves.insert(moves.end(), aux_moves.begin(), aux_moves.end());
            }
            if (board[i][j] == 'G') {
                aux_moves = get_possible_moves_king(i, j, board);
                moves.insert(moves.end(), aux_moves.begin(), aux_moves.end());
            }
        }
    }

    return moves;
}

vector<string> AI::get_possible_moves_pawn(int i, int j, char **board) {
    char capture;
    string move = "";
    vector<string> moves;
    char promotions[] = {'Q', 'R', 'N', 'B'};

    int k = -1;
    if (check_in_bounds(i + 1, j)) {
        if ((board[i + 1][j] == ' ') && (i < 6)) { // Pawn move one without promotion
            board[i + 1][j] = 'P';
            board[i][j] = ' ';
            if (check_check(board)) {
                move += to_string(i) + to_string(j) + to_string(i + 1) +
                        to_string(j) + " ";
                moves.push_back(move);
                move = "";
            }
            board[i][j] = 'P';
            board[i + 1][j] = ' ';
        }
        if ((board[i + 1][j] == ' ') && (i == 6)) { // Pawn move one with promotion
            for (int p = 0; p < 4; p++) {
                board[i][j] = ' ';
                board[i + 1][j] = promotions[p];
                if (check_check(board)) {
                    move += to_string(j) + to_string(j) + " " +
                            promotions[p] + "P";
                    moves.push_back(move);
                    move = "";
                }
                board[i][j] = 'P';
                board[i + 1][j] = ' ';
            }
        }
    }
    if (check_in_bounds(i + 1, j) && check_in_bounds(i + 2, j)) {
        if ((i == 1) && (board[i + 1][j] == ' ') && (board[i + 2][j] == ' ')) { // Pawn move two without promotion
            board[i + 2][j] = board[i][j];
            board[i][j] = ' ';
            if (check_check(board)) {
                move += to_string(i) + to_string(j) + to_string(i + 2) +
                        to_string(j) + " ";
                moves.push_back(move);
                move = "";
            }
            board[i][j] = board[i + 2][j];
            board[i + 2][j] = ' ';
        }
    }
    while (k <= 1) {
        if (check_in_bounds(i + 1, j + k)) {
            if ((islower(board[i + 1][j + k]) != 0) && (i < 6)) { // Pawn capture without promotion
                capture = board[i + 1][j + k];
                board[i][j] = ' ';
                board[i + 1][j + k] = 'P';
                if (check_check(board)) {
                    move += to_string(i) + to_string(j) + to_string(i + 1) +
                            to_string(j + k) + capture;
                    moves.push_back(move);
                    move = "";
                }
                board[i][j] = 'P';
                board[i + 1][j + k] = capture;
            }
            if ((islower(board[i + 1][j + k]) != 0) && (i == 6)) { // Pawn capture with promotion
                for (int p = 0; p < 4; p++) {
                    capture = board[i + 1][j + k];
                    board[i][j] = ' ';
                    board[i + 1][j + k] = promotions[p];
                    if (check_check(board)) {
                        move += to_string(j) + to_string(j + k) + capture +
                                promotions[p] + "P";
                        moves.push_back(move);
                        move = "";
                    }
                    board[i][j] = 'P';
                    board[i + 1][j + k] = capture;
                }
            }
            if (board[i + 1][j + k] == ' ' && board[i][j + k] == 'p' &&
            Facade::last_move[0] == '6' && Facade::last_move[2] == '4' &&
            Facade::last_move[1] == j + k + '0') { // En passant
                capture = board[i][j + k];
                board[i][j] = ' ';
                board[i + 1][j + k] = 'P';
                board[i][j + k] = ' ';
                if (check_check(board)) {
                    move += to_string(i) + to_string(j) + to_string(i + 1) +
                            to_string(j + k) + capture;
                    moves.push_back(move);
                    move = "";
                }
                board[i][j] = 'P';
                board[i + 1][j + k] = ' ';
                board[i][j + k] = capture;

            }
        }
        k += 2;
    }

    return moves;
}

vector<string> AI::get_possible_moves_knight(int i, int j, char **board) {
    char capture;
    string move = "";
    vector<string> moves;
    int i1 = -1, i2 = -1;

    while (i1 <= 1) {
        while (i2 <= 1) {
            if (AI::check_in_bounds(i - i1, j + i2 * 2)) {
                if (islower(board[i - i1][j + i2 * 2]) != 0 || board[i - i1][j + i2 * 2] == ' ') {
                    capture = board[i - i1][j + i2 * 2];
                    board[i][j] = ' ';
                    board[i - i1][j + i2 * 2] = 'K';

                    if (check_check(board)) {
                        move += to_string(i) + to_string(j) + to_string(i - i1) +
                                to_string(j + i2 * 2) + capture;
                        moves.push_back(move);
                        move = "";
                    }
                    board[i][j] = 'K';
                    board[i - i1][j + i2 * 2] = capture;
                }
            }
            if (AI::check_in_bounds(i - i1 * 2, j + i2)) {
                if (islower(board[i - i1 * 2][j + i2]) != 0 || board[i - i1 * 2][j + i2] == ' ') {
                    capture = board[i - i1 * 2][j + i2];
                    board[i][j] = ' ';
                    board[i - i1 * 2][j + i2] = 'K';
                    if (check_check(board)) {
                        move += to_string(i) + to_string(j) + to_string(i - i1 * 2) +
                                to_string(j + i2) + capture;
                        moves.push_back(move);
                        move = "";
                    }
                    board[i][j] = 'K';
                    board[i - i1 * 2][j + i2] = capture;

                }
            }
            i2 += 2;
        }
        i2 = -1;
        i1 += 2;
    }

    return moves;
}

vector<string> AI::get_possible_moves_king(int i, int j, char **board) {
    char capture;
    string move = "";
    vector<string> moves;
    int aux_row_G, aux_column_G;

    for(int c1 = -1; c1 <= 1; c1++){
        for(int c2 = -1; c2 <= 1; c2++){
            if(check_in_bounds(i + c1, j + c2)){
                if((board[i + c1][j + c2] == ' ') ||
                (islower(board[i + c1][j + c2]) != 0)){
                    capture = board[i + c1][j + c2];
                    board[i][j] = ' ';
                    board[i + c1][j + c2] = 'G';

                    aux_row_G = AI::row_G;
                    aux_column_G = AI::column_G;
                    //Change the king position in board
                    AI::row_G = i + c1;
                    AI::column_G = j + c2;

                    if(check_check(board)) {
                        move += to_string(i) + to_string(j) +
                                to_string(i + c1) +
                                to_string(j + c2) + capture;
                        moves.push_back(move);
                        move = "";
                    }
                    AI::column_G = aux_column_G;
                    AI::row_G = aux_row_G;
                    board[i][j] = 'G';
                    board[i + c1][j + c2] = capture;
                }
            }
        }
    }

    move = "";
    //Check castling
    if((!AI::king_moved) &&(check_check(board))) {
        //Check long castling
        if((board[0][1] == ' ') && (board[0][2] == ' ') &&
            (board[0][3] == ' ')) {
            if (!(AI::l_rook_moved)) {
                //Check king safety
                aux_column_G = AI::column_G;
                AI::column_G--;
                if (check_check(board)) {
                    AI::column_G--;
                    if (check_check(board)) {
                        move += to_string(i) + to_string(j) +
                                to_string(i) +
                                to_string(j - 2) + " ";
                        moves.push_back(move);
                        move = "";
                    }
                }
                AI::column_G = aux_column_G;
            }
        }
        //Check short castling
        if((board[0][5] == ' ') && (board[0][6] == ' ')){
            if (!(AI::r_rook_moved)) {
                //Check king safety
                aux_column_G = AI::column_G;
                AI::column_G++;
                if (check_check(board)) {
                    AI::column_G++;
                    if (check_check(board)) {
                        move += to_string(i) + to_string(j) +
                                to_string(i) +
                                to_string(j + 2) + " ";
                        moves.push_back(move);
                    }
                }
                AI::column_G = aux_column_G;
            }
        }
    }

    return moves;
}

vector<string> AI::get_possible_moves_bishop(int i, int j, char **board) {
    char capture;
    string move = "";
    vector<string> moves;
    int c_temp = 1;

    for(int c1 = -1; c1 <= 1; c1+=2){
        for(int c2 = -1; c2 <= 1; c2+=2){
            if(check_in_bounds(i + c_temp * c1, j + c_temp * c2)) {
                while (board[i + c_temp * c1][j + c_temp * c2] == ' ') {
                    capture = board[i + c_temp * c1][j + c_temp * c2];
                    board[i][j] = ' ';
                    board[i + c_temp * c1][j + c_temp * c2] = 'B';
                    if (check_check(board)) {
                        move += to_string(i) + to_string(j) +
                                to_string(i + c_temp * c1) +
                                to_string(j + c_temp * c2) + capture;
                        moves.push_back(move);
                        move = "";
                    }
                    board[i][j] = 'B';
                    board[i + c_temp * c1][j + c_temp * c2] = capture;
                    c_temp++;
                    if(!check_in_bounds(i + c_temp * c1, j + c_temp * c2))
                        break;
                }
                if(check_in_bounds(i + c_temp * c1, j + c_temp * c2)) {
                    if (islower(board[i + c_temp * c1][j + c_temp * c2]) != 0) {
                        capture = board[i + c_temp * c1][j + c_temp * c2];
                        board[i][j] = ' ';
                        board[i + c_temp * c1][j + c_temp * c2] = 'B';
                        if (check_check(board)) {
                            move += to_string(i) + to_string(j) +
                                    to_string(i + c_temp * c1) +
                                    to_string(j + c_temp * c2) + capture;
                            moves.push_back(move);
                            move = "";
                        }
                        board[i][j] = 'B';
                        board[i + c_temp * c1][j + c_temp * c2] = capture;
                    }
                }
            }
            c_temp = 1;
        }
    }

    return moves;
}

vector<string> AI::get_possible_moves_queen(int i, int j, char **board) {
    char capture;
    string move = "";
    vector<string> moves;
    int c_temp = 1;

    for(int c1 = -1; c1 <= 1; c1++){
        for(int c2 = -1; c2 <= 1; c2++){
            if(check_in_bounds(i + c_temp * c1, j + c_temp * c2)) {
                while (board[i + c_temp * c1][j + c_temp * c2] == ' ') {
                    capture = board[i + c_temp * c1][j + c_temp * c2];
                    board[i][j] = ' ';
                    board[i + c_temp * c1][j + c_temp * c2] = 'Q';
                    if (check_check(board)) {
                        move += to_string(i) + to_string(j) +
                                to_string(i + c_temp * c1) +
                                to_string(j + c_temp * c2) + capture;
                        moves.push_back(move);
                        move = "";
                    }
                    board[i][j] = 'Q';
                    board[i + c_temp * c1][j + c_temp * c2] = capture;
                    c_temp++;
                    if(!check_in_bounds(i + c_temp * c1, j + c_temp * c2))
                        break;
                }
                if(check_in_bounds(i + c_temp * c1, j + c_temp * c2)) {
                    if (islower(board[i + c_temp * c1][j + c_temp * c2]) != 0) {
                        capture = board[i + c_temp * c1][j + c_temp * c2];
                        board[i][j] = ' ';
                        board[i + c_temp * c1][j + c_temp * c2] = 'Q';
                        if (check_check(board)) {
                            move += to_string(i) + to_string(j) +
                                    to_string(i + c_temp * c1) +
                                    to_string(j + c_temp * c2) + capture;
                            moves.push_back(move);
                            move = "";
                        }
                        board[i][j] = 'Q';
                        board[i + c_temp * c1][j + c_temp * c2] = capture;
                    }
                }
            }
            c_temp = 1;
        }
    }

    return moves;
}

vector<string> AI::get_possible_moves_rook(int i, int j, char **board) {
    char capture;
    string move = "";
    vector<string> moves;
    int c_temp = 1;

    for(int c1 = -1; c1 <= 1; c1++){
        for(int c2 = -1; c2 <= 1; c2++){
            if(check_in_bounds(i + c_temp * c1, j + c_temp * c2) &&
               ((c1 == 0) || (c2 == 0))) {
                while (board[i + c_temp * c1][j + c_temp * c2] == ' ') {
                    capture = board[i + c_temp * c1][j + c_temp * c2];
                    board[i][j] = ' ';
                    board[i + c_temp * c1][j + c_temp * c2] = 'R';
                    if(check_check(board)) {
                        move += to_string(i) + to_string(j) +
                                to_string(i + c_temp * c1) +
                                to_string(j + c_temp * c2) + " ";
                        moves.push_back(move);
                        move = "";
                    }
                    board[i][j] = 'R';
                    board[i + c_temp * c1][j + c_temp * c2] = capture;
                    c_temp++;
                    if(!check_in_bounds(i + c_temp * c1, j + c_temp * c2))
                        break;
                }
                if(check_in_bounds(i + c_temp * c1, j + c_temp * c2)) {
                    if (islower(board[i + c_temp * c1][j + c_temp * c2]) != 0) {
                        capture = board[i + c_temp * c1][j + c_temp * c2];
                        board[i][j] = ' ';
                        board[i + c_temp * c1][j + c_temp * c2] = 'R';
                        if(check_check(board)){
                            move += to_string(i) + to_string(j) +
                                    to_string(i + c_temp * c1) +
                                    to_string(j + c_temp * c2) + capture;
                            moves.push_back(move);
                            move = "";
                        }
                        board[i][j] = 'R';
                        board[i + c_temp * c1][j + c_temp * c2] = capture;
                    }
                }
            }
            c_temp = 1;
        }
    }

    return moves;
}

bool AI::check_check(char **board){

    int c_temp = 1;

    // Queen or Bishop
    for (int i1 = -1; i1 <= 1; i1 += 2) {
        for (int i2 = -1; i2 <= 1; i2 += 2) {
            if (check_in_bounds(row_G + c_temp * i1, column_G + c_temp * i2)) {
                while (board[row_G + c_temp * i1][column_G + c_temp * i2] == ' ') {
                    if (!check_in_bounds(row_G + (c_temp + 1) * i1, column_G
                        + (c_temp + 1) * i2))
                        break;
                    c_temp++;
                }
            }
            if (check_in_bounds(row_G + c_temp * i1, column_G + c_temp * i2)) {
                if (board[row_G + c_temp * i1][column_G + c_temp * i2] == 'b' ||
                    board[row_G + c_temp * i1][column_G + c_temp * i2] == 'q') {
                    return false;
                }
            }
            c_temp = 1;
        }
    }

    // Rook or queen
    for (int i1 = -1; i1 <= 1; i1 += 2) {
        if (check_in_bounds(row_G, column_G + c_temp * i1)) {
            while (board[row_G][column_G + c_temp * i1] == ' ') {
                if (!check_in_bounds(row_G, column_G + (c_temp + 1) * i1)) {
                    break;
                } else {
                    c_temp++;
                }
            }
        }
        if (check_in_bounds(row_G, column_G + c_temp * i1)) {
            if (board[row_G][column_G + c_temp * i1] == 'r' ||
                board[row_G][column_G + c_temp * i1] == 'q') {
                return false;
            }
        }
        c_temp = 1;
        if (check_in_bounds(row_G + c_temp * i1, column_G)) {
            while (board[row_G + c_temp * i1][column_G] == ' ') {
                if (!check_in_bounds(row_G + (c_temp + 1) * i1, column_G)) {
                    break;
                } else {
                    c_temp++;
                }
            }
        }
        if (check_in_bounds(row_G + c_temp * i1, column_G)) {
            if (board[row_G + c_temp * i1][column_G] == 'r' ||
                board[row_G + c_temp * i1][column_G] == 'q') {
                return false;
            }
        }
        c_temp = 1;
    }

// Knight
    for (int i1 = -1; i1 <= 1; i1 += 2) {
        for (int i2 = -1; i2 <= 1; i2 += 2){
            if (check_in_bounds(row_G + i1, column_G + i2 * 2) &&
                board[row_G + i1][column_G + i2 * 2] == 'k') {
                return false;
            }
            if (check_in_bounds(row_G + i1 * 2, column_G + i2) &&
                board[row_G + i1 * 2][column_G + i2] == 'k') {
                return false;
            }
        }
    }

    // Pawn
    if (check_in_bounds(row_G + 1, column_G - 1)){
        if (board[row_G + 1][column_G - 1] == 'p') {
            return false;
        }
    }
    if (check_in_bounds(row_G + 1, column_G + 1)){
        if (board[row_G + 1][column_G + 1] == 'p') {
            return false;
        }
    }

    // King
    for (int i1 = -1; i1 <= 1; i1++) {
        for (int i2 = -1; i2 <= 1; i2++) {
            if (i1 != 0 || i2 != 0) {
                if (check_in_bounds(row_G + i1, column_G + i2) &&
                    board[row_G + i1][column_G + i2] == 'g') {
                    return false;
                }
            }
        }
    }

    return true;
}

string AI::think_move(vector<string> moves) {
    int random = rand() % moves.size();

    //check if castling pieces moved
    if((moves[random].at(0) == '0')&& moves[random].at(1) == '0')
        AI::l_rook_moved = true;
    if((moves[random].at(0) == '0')&& moves[random].at(1) == '7')
        AI::r_rook_moved = true;
    if((moves[random].at(0) == '0')&& moves[random].at(1) == '4')
        AI::king_moved = true;

    return moves[random];
}
