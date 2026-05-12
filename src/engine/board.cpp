//
// Created by peter on 2026. 05. 02..
//

#include <iostream>
#include <vector>
#include "engine.h"



Position::Position(const int x, const int y) : x(x), y(y) {}

void Position::print() const {
    std::cout << x << " " << y << std::endl;
}

bool Position::upgrade(const std::string& color, const std::string& name) {
    if (color == "white" && name == "pawn" && y == 8) return true;
    if (color == "black" && name == "pawn" && y == 0) return true;
    return false;
}

bool Position::inside() {
    if (x >= 0 && x <= 8 && y >= 0 && y <= 8) return true;
    return false;
}



Moves::Moves(const std::vector<Position>& moves, const std::vector<Position>& captures, const std::vector<std::vector<Position>> moves_sections,std::vector<int> captures_section_mask) : moves(moves), captures(captures), moves_sections(moves_sections), captures_section_mask(captures_section_mask) {}


Player::Player(const std::string& name, const std::string color) :  name(name), color(color) {}


void Player::init_pieces() {

    int y = 1;
    if (color == "white") {
        y = 1;
        pieces.push_back(Piece("King", Position(4,0),color));
        pieces.push_back(Piece("Queen", Position(5,0),color));

        pieces.push_back(Piece("Rook", Position(0,0),color));
        pieces.push_back(Piece("Knight", Position(1,0),color));
        pieces.push_back(Piece("Bishop", Position(3,0),color));

        pieces.push_back(Piece("Rook", Position(8,0),color));
        pieces.push_back(Piece("Knight", Position(7,0),color));
        pieces.push_back(Piece("Bishop", Position(6,0),color));

        for (int i = 0; i < 8; i++) {
            pieces_pawns.push_back(Piece(color, Position(i,y),color));
        }
    }
    else if (color == "black") {
        y = 7;
        pieces.push_back(Piece("King", Position(4,8),color));
        pieces.push_back(Piece("Queen", Position(5,8),color));

        pieces.push_back(Piece("Rook", Position(0,8),color));
        pieces.push_back(Piece("Knight", Position(1,8),color));
        pieces.push_back(Piece("Bishop", Position(3,8),color));

        pieces.push_back(Piece("Rook", Position(8,8),color));
        pieces.push_back(Piece("Knight", Position(7,8),color));
        pieces.push_back(Piece("Bishop", Position(6,8),color));

        for (int i = 0; i < 8; i++) {
            pieces_pawns.push_back(Piece(color, Position(i,y),color));
        }
    }
    std::cout << "Adding pawns" << std::endl;
}


void Player::apply_move(const std::string &piece_name, const Position pos, Player& player) {

    for (auto p : pieces) {
        if (p.name == piece_name) {
            for (auto valid_move : p.moves_history.back().moves) {
                if (check_postion(pos,valid_move)) {
                    p.set_position(pos);
                    return;
                }
            }for (auto valid_move : p.moves_history.back().captures) {
                if (check_postion(pos,valid_move)) {
                    p.set_position(pos);
                    player.remove_piece(valid_move);
                    //remove teh piece at the given position
                    return;
                }
            }

        }
    }
}


void Player::remove_piece(const Position pos) {
    //auto& piece = pieces;

    std::erase_if(pieces, [&](const auto& p) {
        return check_postion(p.position, pos);
    });
}

void Board::remove_piece(std::string color, const Position pos) {
    int index = color == "white" ? 1 : 0;

    auto& pieces = players[index].pieces;

    std::erase_if(pieces, [&](const auto& p) {
        return check_postion(p.position, pos);
    });

}

Piece::Piece(const std::string& name, const Position position, const std::string color) : position(position), name(name), color(color) {
}

void Piece::print_position(){}
Position Piece::get_position() const { return position; }
//std::vector<std::vector<Position>> get_valid_moves() const {}

Moves Piece::move(const Board& board)  {
    Moves move = moves_generation(board, *this);
    moves_history.push_back(move);
    return move;
}

void Piece::set_position(const Position& pos) { position.x=pos.x; position.y=pos.y; }






void Board::print() const {}


void Board::initialize() {
    players.push_back(Player("Player 1" , "white"));
    players.push_back(Player("Player 2","black"));

    for ( auto& player : players) {
        player.init_pieces();
    }
}



