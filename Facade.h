#ifndef PROIECT_PA_FACADE_H
#define PROIECT_PA_FACADE_H

#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <fstream>
#include "Board.h"
#include "AI.h"
#include "Engine.h"

using namespace std;

class Facade {

public:
    Facade();

    ~Facade();

    static string last_move;

    static string move;

    static void send_features(const string& string);

    static vector<string> get_cmd_words();

    static void init_board(Board *board, char initialBoard[8][8]);

    static void update_board(Board *board, string move);

    static void make_and_send_move(Board *board);

    static void mirror_board(Board *board);

    static void engine_stop();

    static void engine_start();

    static void white();

    static void black();

    static bool is_white();

    static bool is_black();

    static void verify_graphical();

};

#endif //PROIECT_PA_FACADE_H
