#ifndef PROIECT_ENGINE_H
#define PROIECT_ENGINE_H

#include <iostream>

using namespace std;


class Engine {
public:
    static bool white;

    static bool running;

    Engine();

    ~Engine();

    static void make_move(char **board, string move, string last_move);

    static void make_move_opp(char **board, string move, string last_move);

    static void set_white(bool white);

    static void set_running(bool running);
};


#endif //PROIECT_ENGINE_H
