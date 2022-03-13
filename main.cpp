#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include "Facade.h"
#include "Board.h"
#include "AI.h"


using namespace std;

int main(){


    char initial_board[8][8] = {
            {'R','K','B','Q','G','B','K','R'}, // BIG LETTER -> Black; small letter -> White;
            {'P','P','P','P','P','P','P','P'}, // R/r -> Rook(turn)
            {' ',' ',' ',' ',' ',' ',' ',' '}, // K/k -> Knight(cal)
            {' ',' ',' ',' ',' ',' ',' ',' '}, // B/b -> Bishop(nebun)
            {' ',' ',' ',' ',' ',' ',' ',' '}, // Q/q -> Queen(regina)
            {' ',' ',' ',' ',' ',' ',' ',' '}, // G/g -> King(rege)
            {'p','p','p','p','p','p','p','p'}, // P/p -> Pawn(pion)
            {'r','k','b','q','g','b','k','r'}
/*            {'R','K','B','Q','G','B','K','R'}, // BIG LETTER -> Black; small letter -> White;
            {'P','P','P','P','P','P','P','P'}, // R/r -> Rook(turn)
            {' ',' ',' ',' ',' ',' ',' ',' '}, // K/k -> Knight(cal)
            {' ',' ',' ',' ',' ',' ',' ',' '}, // B/b -> Bishop(nebun)
            {' ',' ',' ',' ',' ',' ',' ',' '}, // Q/q -> Queen(regina)
            {' ',' ',' ',' ',' ',' ',' ',' '}, // G/g -> King(rege)
            {'p','p','p','p','p','p','p','p'}, // P/p -> Pawn(pion)
            {'r','k','b','q','g','b','k','r'}*/
    };

    auto *board = new Board();

    // Disable buffers
    cout.rdbuf()->pubsetbuf(nullptr, 0);
    cin.rdbuf()->pubsetbuf(nullptr, 0);

    Facade::verify_graphical();

    while(true){

        vector<string> cmd_words = Facade::get_cmd_words();

        if (cmd_words[0] == "protover") {
            Facade::send_features(cmd_words.back());
        }
        
        if (cmd_words[0] == "accepted") {
        }
        
        if (cmd_words[0] == "new") {
            Facade::black();
            Facade::init_board(board, initial_board);
            Facade::engine_start();
        }

        if ((isalpha(cmd_words[0][0])) && isdigit(cmd_words[0][1])) {
            Facade::update_board(board, cmd_words[0]);
            Facade::make_and_send_move(board);
        }

        if (cmd_words[0] == "white" && Facade::is_black()) {
            Facade::white();
            Facade::mirror_board(board);
        }

        if (cmd_words[0] == "black" && Facade::is_white()) {
            Facade::black();
            Facade::mirror_board(board);
        }

        if (cmd_words[0] == "go") {
            Facade::engine_start();
            Facade::make_and_send_move(board);
        }

        if (cmd_words[0] == "force") {
            Facade::engine_stop();
        }

        if(cmd_words[0] == "quit"){
            break;
        }

    }

    return 0;
}
