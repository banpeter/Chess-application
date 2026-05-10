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

//TODO also do overlap checking with the same color
bool check_move(const Board& board, const Position next_pos) {

    int overlap = -1;

    for (const auto& player : board.players) {
        for (const auto& pl : player.pieces) {
            if (check_postion(next_pos,pl.position)) {
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

    bool inside = true;
    bool capture = false;

    inside = next_position.inside();
    capture = check_move(board,current_position);//TODO

    if (inside && !capture) {

    }
    else if (inside && capture) {


    }
    else if (!inside) {
        return false;
    }


    return false;
}
int color_to_index(const std::string& color) {
    if (color == "white") {
        return 0;
    }
    if (color == "black") {
        return 1;
    }
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
//TODO piece can not move if attacks could happen -> each ,moves has to go until boundary??
//TODO add resign
bool check_mate(const Board& board, const Piece& king) {

    std::vector<std::vector<Position>> moves_sections;
    std::vector<Piece> attacking_pieces;

    //find attacking piceces and the coresponding section of moves
    //
    int color = -1;

    if (king.color == "white") {
        color = 0;
    }
    else if (king.color == "black") {
        color = 1;
    }

    for(auto p : board.players[color].pieces) {
        Moves moves = p.moves_history.back();
        for (const auto & move : moves.moves_sections) {
            for (const auto & pos : move) {
                if (king.position.x == pos.x && king.position.y == pos.y) {
                    attacking_pieces.push_back(p);
                    moves_sections.push_back(move);
                    //return true;
                }
            }
        }
    }
    if (attacking_pieces.size()>1) {
        return true;
    }

    //check and no more valide moves
    if (attacking_pieces.size() == 1 && king.moves_history.back().moves.empty()) {
        return true;
    }
    //TODO additional rules and constraints can be added
    //plus TODO find if other pieces can attack the attaking piceces
    //plus TODO find if other pieces can interfer

    for(auto p : board.players[1].pieces) {
        p.move(board);
    }

    return false;

}

