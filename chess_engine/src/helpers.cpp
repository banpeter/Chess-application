//
// Created by peter on 2026. 05. 02..
//

#include "engine.h"

bool check_postion(const Position p1, const Position p2) {
    if (p1.x == p2.x && p1.y == p2.y) {
        return true;
    }
    return false;
}


bool check_move(const Board& board, const Position current_pos) {

    int overlap = -1;

    for (const auto& player : board.players) {
        for (const auto& pl : player.pieces) {
            if (check_postion(current_pos,pl.position)) {
                overlap++;
                if (overlap == 1) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool validate(Position current_position, Position next_position,Board board) {

    //TODO pass these as pointers
    std::vector<Position> moves;
    std::vector<Position> captures;

    bool inside = true;
    bool capture = false;

    inside = next_position.inside();
    capture = check_move(board,current_position);//TODO

    if (inside && !capture) {
        moves.push_back(next_position);
    }
    else if (inside && capture) {
        captures.push_back(next_position);

    }
    else if (!inside) {
        return false;
    }


    return false;
}

std::vector<Position> intersection(const std::vector<Position>& moves1, const std::vector<Position> moves2) {

    std::vector<Position> intersection;

    for (const auto & i : moves1) {
        for (const auto & j : moves2) {
            if (check_postion(i,j)) {
                intersection.push_back(i);
            }
        }
    }
    return intersection;
}