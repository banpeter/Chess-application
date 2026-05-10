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


int evaluate(const Board& board,std::string color) {
    int white_value = 0;
    int black_value = 0;
    for(auto p : board.players[0].pieces) {
        white_value+=value(p.name);
    }
    for(auto p : board.players[1].pieces) {
        black_value+=value(p.name);
    }

    if (color == "white") {
        return white_value-black_value;
    }
    else if (color == "black") {
        return black_value-white_value;
    }

    return 0;
}

int minimax(const Board& board,int depth, int alpha, int beta,bool is_maximizing) {
    std::vector<Moves> possible_moves;
    std::vector<Board> possible_boards;


    //for each move create updated board

    //generate_moves
    for(auto p : board.players[0].pieces) {
        auto move = p.move(board);
        possible_moves.push_back(move);
    }


    if (is_maximizing) {
        int best = std::numeric_limits<int>::min();

        for (const Board& child : possible_boards) {
            int score = minimax(child, depth - 1, alpha, beta, false);
            best  = std::max(best, score);
            alpha = std::max(alpha, best);

            if (beta <= alpha)
                break;
        }
        return best;

    } else {
        int best = std::numeric_limits<int>::max();

        for (const Board& child : possible_boards) {
            int score = minimax(child, depth - 1, alpha, beta, true);
            best = std::min(best, score);
            beta = std::min(beta, best);

            if (beta <= alpha)
                break;
        }
        return best;
    }

}




// Find the best move from root
int best_move(const Board& root, int depth, std::string color) {
    int best_score = std::numeric_limits<int>::min();
    int best_idx   = -1;
    int alpha      = std::numeric_limits<int>::min();
    int beta       = std::numeric_limits<int>::max();

    for (int i = 0; i < root.children.size(); i++) {
        int score = minimax(root.children[i], depth - 1, alpha, beta, false);
        if (score > best_score) {
            best_score = score;
            best_idx   = i;
        }
        alpha = std::max(alpha, best_score);
    }

    return best_idx;
}