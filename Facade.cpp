#include "Facade.h"

using namespace std;

string Facade::last_move;
string Facade::move;

Facade::Facade() = default;

Facade::~Facade() = default;

void Facade::send_features(const string& string) {
    // Verify if it's the right version of Xboard (i.e. 2)
    if (stoi(string) != 2) {
        exit(1);
    }
    cout << "feature sigint=0 san=0 done=1" << endl;
}

void Facade::init_board(Board *board, char initial_board[8][8]) {
    board->set_default_board(initial_board);
    Engine::set_white(false);
}

void Facade::verify_graphical() {
    string graphical_software;
    getline(cin, graphical_software);
    if (graphical_software != "xboard") {
        exit(1);
    }
}

vector<string> Facade::get_cmd_words() {
    string cmd;
    getline(cin, cmd);
    istringstream iss(cmd);
    vector<string> cmd_words{istream_iterator<string>{iss},
                            istream_iterator<string>{}};
    return cmd_words;
}

void Facade::update_board(Board *board, string curr_move) {
    if (Engine::white) {
        last_move = "";
        last_move = AI::convert_move_white(curr_move);
        Engine::make_move_opp(board->board, last_move, move);
    } else {
        last_move = "";
        last_move = AI::convert_move(curr_move);
        Engine::make_move_opp(board->board, last_move, move);
    }
}

void Facade::make_and_send_move(Board *board) {
    if (Engine::running) {
        vector<string> moves = AI::get_possible_moves(board->board);
        if (moves.size() < 1) {
            Facade::engine_stop();
        } else {
            move = "";
            move = AI::think_move(moves);
            Engine::make_move(board->board, move, last_move);
            if (Engine::white) {
                cout << "move " << AI::unconvert_move_white(move) << endl;
            } else {
                cout << "move " << AI::unconvert_move(move) << endl;
            }
        }
    }
}

void Facade::mirror_board(Board *board) {
    board->mirror();
}

void Facade::white() {
    Engine::set_white(true);
}

void Facade::black() {
    Engine::set_white(false);
}

bool Facade::is_white() {
    return Engine::white;
}

bool Facade::is_black() {
    return !Engine::white;
}

void Facade::engine_stop() {
    Engine::set_running(false);
}

void Facade::engine_start() {
    Engine::set_running(true);
}


