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


bool check_move(const Board& board, const Position next_pos, std::string color) {

    int index = color == "white" ? 1 : 0;
    int overlap = 0;


    for (const auto& pl : board.players[index].pieces) {
        if (check_postion(next_pos,pl.position)) {
            overlap++;
            if (overlap == 1) {
                return true;
            }
        }
    }

    return false;
}

bool check_occupied(const Board& board, const Position next_pos) {

        int overlap = 0;

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




int color_to_index(const std::string& color) {
    if (color == "white") {
        return 0;
    }
    if (color == "black") {
        return 1;
    }
    return -1;
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

//check if
bool check(const Board& board, const Piece& king) {

    const Player *p = nullptr;
    const Player *p2 = nullptr;

    if (king.color == "white") {
        p = &board.players[0];
        p2 = &board.players[1];
    }
    else {
        p = &board.players[1];
        p2 = &board.players[0];
    }
    for (const auto & piece : p2->pieces) {
        if (!piece.moves_history.empty() && !piece.moves_history.back().moves.empty()) {
            for (const auto& move : piece.moves_history.back().moves) {
                if (move.x == king.position.x && move.y == king.position.y) {
                    return true;
                }
            }
        }

    }
    return false;
}

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

    for(auto p : board.players[1].pieces) {
        p.move(board);
    }

    return false;

}

void promote_pawn(Board& board, const Position pos, const std::string piece_name, std::string color) {
    //find piece based on position
    //based on name create a new piece
    int index = color == "white" ? 0 : 1;

    //check if promotion is valid

    for(auto p : board.players[index].pieces) {
        if (p.name == piece_name && check_postion(pos,p.position)) {
            std::erase_if(board.players[index].pieces, [&pos](const Piece& p) {
                return p.position.x == pos.x && p.position.y == pos.y;
            });
            //upgrade
            if (piece_name == "Rook") {
                board.players[index].pieces.push_back(Piece("Rook", Position(pos.x,pos.y),color));
            }
            else if (piece_name == "Knight") {
                board.players[index].pieces.push_back(Piece("Knight", Position(pos.x,pos.y),color));
            }
            else if (piece_name == "Bishop") {
                board.players[index].pieces.push_back(Piece("Bishop", Position(pos.x,pos.y),color));
            }
            else if (piece_name == "Queen") {
                board.players[index].pieces.push_back(Piece("Queen", Position(pos.x,pos.y),color));
            }
            return;
        }
    }


}