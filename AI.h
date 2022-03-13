#ifndef PROIECT_PA_AI_H
#define PROIECT_PA_AI_H

#include <string>
#include <vector>
#include <iostream>
#include "Facade.h"

using namespace std;

class AI {
public:
    AI();

    ~AI();

    static int row_G;

    static int column_G;

    static bool king_moved;

    static bool l_rook_moved;

    static bool r_rook_moved;

    static string convert_move(string move);

    static string unconvert_move(string move);

    static string convert_move_white(string move);

    static string unconvert_move_white(string move);

    static bool check_in_bounds(int i, int j);

    static vector<string> get_possible_moves(char **board);

    static vector<string> get_possible_moves_pawn(int i, int j, char **board);

    static vector<string> get_possible_moves_knight(int i, int j, char **board);

    static vector<string> get_possible_moves_king(int i, int j, char **board);

    static vector<string> get_possible_moves_bishop(int i, int j, char **board);

    static vector<string> get_possible_moves_queen(int i, int j, char **board);

    static vector<string> get_possible_moves_rook(int i, int j, char **board);

    static bool check_check(char **board);

    static string think_move(vector<string> moves);
};


#endif //PROIECT_PA_AI_H
