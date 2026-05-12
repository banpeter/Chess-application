//
// Created by peter on 2026. 04. 26..
//
#include <iostream>
#include <limits>

#include "engine.h"

#define MAX_DEPTH 20

int value(std::string name) {

    if (name == "pawn") {
        return 2;
    }
    if (name == "knight") {
        return 3;
    }
    if (name == "bishop") {
        return 4;
    }
    if (name == "rook") {
        return 5;
    }
    if (name == "queen") {
        return 10;
    }
    if (name == "king") {
        return 7;
    }

    return 0;
}


int evaluate(const Board& board,unsigned int index, unsigned int index2) {
    int white_value = 0;
    int black_value = 0;
    for(auto p : board.players[index].pieces) {
        white_value+=value(p.name);
    }
    for(auto p : board.players[index2].pieces) {
        black_value+=value(p.name);
    }

    if (index == 0) {
        return white_value-black_value;
    }
    if (index == 1) {
        return black_value-white_value;
    }

    return 0;
}

Board apply_move(Board board,std::string piece_name, Position pos, unsigned int index, unsigned int index2) {


    for(auto p : board.players[index].pieces) {
        if (p.name == piece_name) {
            for (auto valid_move : p.moves_history.back().moves) {
                if (check_postion(pos,valid_move)) {
                    p.set_position(pos);
                    return board;
                }
            }for (auto valid_move : p.moves_history.back().captures) {
                if (check_postion(pos,valid_move)) {
                    p.set_position(pos);
                    board.players[index2].remove_piece(valid_move);
                    //remove teh piece at the given position
                    return board;
                }
            }

        }
    }
    return board;
}

//TODO add checkmate
int minimax(Board board,int depth, int alpha, int beta,bool is_maximizing, unsigned int index, unsigned int index2) {



    if (depth > 50) {
        return evaluate(board,index,index2);
    }


    unsigned int ind = index;
    index = index2;
    index2 = ind;



    std::vector<Moves> possible_moves;
    std::vector<std::string> piece_names;
    std::vector<Board> possible_boards;

    //for each move create updated board

    //generate_moves
    for(auto p : board.players[index].pieces) {
        auto move = p.move(board);
        possible_moves.push_back(move);
    }
    //APPLY moves -> possible boards
    for (int i = 0; i < possible_moves.size(); i++) {
        for (int j = 0; j < possible_moves[i].moves.size(); j++) {
            Board pboard= apply_move(board,piece_names[i],possible_moves[i].moves[j],index2,index2);
            possible_boards.push_back(pboard);
        }
        for (int j = 0; j < possible_moves[i].moves.size(); j++) {
            Board pboard= apply_move(board,piece_names[i],possible_moves[i].captures[j],index2,index2);
            possible_boards.push_back(pboard);
        }

    }



    if (is_maximizing) {
        int best = std::numeric_limits<int>::min();

        for (const Board& child : possible_boards) {
            int score = minimax(child, depth - 1, alpha, beta, false, index,  index2);
            best  = std::max(best, score);
            alpha = std::max(alpha, best);

            if (beta <= alpha)
                break;
        }
        return best;

    } else {
        int best = std::numeric_limits<int>::max();

        for (const Board& child : possible_boards) {
            int score = minimax(child, depth - 1, alpha, beta, true,   index,   index2);
            best = std::min(best, score);
            beta = std::min(beta, best);

            if (beta <= alpha)
                break;
        }
        return best;
    }

}




// Find the best move from root
int best_move(Board root, int depth, std::string color, int which_player) {
    int best_score = std::numeric_limits<int>::min();
    int best_idx   = -1;
    int alpha      = std::numeric_limits<int>::min();
    int beta       = std::numeric_limits<int>::max();

    unsigned int index;
    unsigned int index2;

    if (which_player == 0) {
        index = 0;
        index2 = 1;
    }
    else {
        index = 1;
        index2 = 0;
    }
    index += which_player;


    int score = minimax(root, depth - 1, alpha, beta, false, index, index2);

    return best_idx;
}