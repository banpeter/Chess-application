//
// Created by peter on 2026. 05. 02..
//
#include <iostream>
#include <ostream>

#include "engine.h"


Moves rook_moves(const Board& board, const Piece& chosen_piece) {
    std::vector<Position> moves_pos;
    std::vector<Position> captures;
    std::vector<int> captures_mask;
    std::vector<std::vector<Position>> moves_sections;

    Position next_position = chosen_piece.position;
    bool inside = true;
    bool occupied = true;
    bool capture = false;

    bool generate = true;

    for (int i = 0; i < 4; i++) {
        std::vector<Position> moves_section;
        while (generate) {
            if (i==0) {
                next_position.x--;
            }
            else if (i==1) {
                next_position.x++;
            }
            else if (i==2) {
                next_position.y++;
            }
            else if (i==3) {
                next_position.y--;
            }

            //check inside
            inside = next_position.inside();
            occupied = check_occupied(board,next_position);
            capture = check_move(board,next_position,chosen_piece.color);

            if (inside && !occupied && !capture) {
                captures_mask.push_back(0);
                moves_pos.push_back(next_position);
            }
            else if (inside && occupied && !capture) {
                generate = false;
            }
            else if (inside && occupied && capture) {
                captures.push_back(next_position);
                captures_mask.push_back(1);
                generate = false;
            }
            else if (!inside) {
                captures_mask.push_back(0);
                generate = false;
            }
            moves_section.push_back(next_position);//TODO wrong place
        }
        moves_sections.push_back(moves_section);
        next_position = chosen_piece.position;
        generate = true;

    }

    auto moves = Moves(moves_pos,captures,moves_sections,captures_mask);
    return moves;
}


Moves bishop_moves(const Board& board, const Piece& chosen_piece) {
    std::vector<Position> moves_pos;
    std::vector<Position> captures;
    std::vector<int> captures_mask;
    std::vector<std::vector<Position>> moves_sections;

    Position next_position = chosen_piece.position;
    bool inside = true;
    bool occupied = true;
    bool capture = false;

    bool generate = true;

    for (int i = 0; i < 4; i++) {
        std::vector<Position> moves_section;
        while (generate) {
            if (i==0) {
                next_position.x++;
                next_position.y++;
            }
            else if (i==1) {
                next_position.x--;
                next_position.y--;
            }
            else if (i==2) {
                next_position.x--;
                next_position.y++;
            }
            else if (i==3) {
                next_position.x++;
                next_position.y--;
            }
            //next_position.x++;
            //next_position.y++;
            //check inside
            inside = next_position.inside();
            occupied = check_occupied(board,next_position);
            capture = check_move(board,next_position,chosen_piece.color);

            if (inside && !occupied && !capture) {
                captures_mask.push_back(0);
                moves_pos.push_back(next_position);
            }
            else if (inside && occupied && !capture) {
                generate = false;
            }
            else if (inside && occupied && capture) {
                captures.push_back(next_position);
                captures_mask.push_back(1);
                generate = false;
            }
            else if (!inside) {
                captures_mask.push_back(0);
                generate = false;
            }
            moves_section.push_back(next_position);
        }
        moves_sections.push_back(moves_section);
        next_position = chosen_piece.position;
        generate = true;
    }


    auto moves = Moves(moves_pos,captures,moves_sections,captures_mask);
    return moves;
}


Moves knight_moves(const Board& board, const Piece& chosen_piece) {
    std::vector<Position> moves_pos;
    std::vector<Position> captures;

    std::vector<int> captures_mask;
    std::vector<std::vector<Position>> moves_sections;

    Position next_position = chosen_piece.position;
    bool inside = true;
    bool occupied = true;
    bool capture = false;

    const std::vector<std::vector<int>> move_knight = {{2,1},  {2,-1},  {-2,1}, {-2,-1}, {1, 2}, {-1,2},{-1, -2}, {1,-2}  };

    for (auto& move : move_knight) {
        std::vector<Position> moves_section;
        next_position.x += move[0];
        next_position.y += move[1];
        inside = next_position.inside();
        occupied = check_occupied(board,next_position);
        capture = check_move(board,chosen_piece.position,chosen_piece.color);
        if (inside && !occupied && !capture) {
            captures_mask.push_back(0);
            moves_pos.push_back(next_position);
        }

        else if (inside && occupied && capture) {

            captures_mask.push_back(1);
            captures.push_back(next_position);
        }
        moves_section.push_back(next_position);
        next_position = chosen_piece.position;
        moves_sections.push_back(moves_section);
    }
    auto moves = Moves(moves_pos,captures,moves_sections,captures_mask);
    return moves;
}


Moves pawn_moves(const Board& board, const Piece& chosen_piece) {
    std::vector<Position> moves_pos;
    std::vector<Position> captures;

    std::vector<int> captures_mask;
    std::vector<std::vector<Position>> moves_sections;

    Position next_position = chosen_piece.position;
    bool inside = true;
    bool occupied = true;
    bool capture = false;
    int first_move = 2;

    const std::vector<std::vector<int>> move_pawn_white = {{0,1},  {1,1},  {-1,1} };
    const std::vector<std::vector<int>> move_pawn_black = {{0,-1},  {1,-1},  {-1,-1}};

    const std::vector<std::vector<int>> *move_pawn = nullptr;
    if (chosen_piece.color == "white") {
        move_pawn = &move_pawn_white;
    }
    else if (chosen_piece.color == "black") {
        move_pawn = &move_pawn_black;
        first_move = -2;
    }
    std::vector<Position> moves_section;
    if (!chosen_piece.moved) {
        next_position.x += 0;
        next_position.y += first_move;
        inside = next_position.inside();
        occupied = check_occupied(board,next_position);
        capture = check_move(board,chosen_piece.position,chosen_piece.color);
        if (inside && !occupied && !capture) {
            captures_mask.push_back(0);

            moves_pos.push_back(next_position);
        }
        moves_section.push_back(next_position);
        moves_sections.push_back(moves_section);
        next_position.x += 0;
        next_position.y -= first_move;
    }


    for (int i = 0; i < move_pawn->size(); i++) {


        next_position.x += (*move_pawn)[i][0];
        next_position.y += (*move_pawn)[i][1];

        inside = next_position.inside();
        occupied = check_occupied(board,next_position);
        capture = check_move(board,next_position,chosen_piece.color);



        if (inside && !occupied && !capture && i == 0) {
            captures_mask.push_back(0);
            moves_pos.push_back(next_position);
        }
        else if (inside && occupied && capture && i != 0) {
            captures_mask.push_back(1);
            captures.push_back(next_position);
        }
        moves_section.push_back(next_position);
        moves_sections.push_back(moves_section);
        next_position = chosen_piece.position;

    }
    //std::cout << "Pawn Moves generated" << std::endl;
    auto moves = Moves(moves_pos,captures,moves_sections,captures_mask);
    return moves;
}


//Apply: Bishop+Rook
Moves queen_moves(const Board& board, const Piece& chosen_piece) {
    std::vector<Position> moves_pos;
    std::vector<Position> captures;

    std::vector<std::vector<Position>> moves_sections;
    std::vector<int> captures_mask;

    MoveFunction rook_moves_generation = rook_moves;
    MoveFunction bishop_moves_generation = bishop_moves;

    Moves r_moves = rook_moves_generation(board,chosen_piece);
    Moves b_moves = bishop_moves_generation(board,chosen_piece);

    for ( const auto & i : r_moves.moves) {
        moves_pos.push_back(i);
    }
    for ( const auto & i : r_moves.captures) {
        moves_pos.push_back(i);
    }

    for ( const auto & i : r_moves.moves_sections) {
        moves_sections.push_back(i);
    }
    for ( const auto & i : r_moves.captures_section_mask) {
        captures_mask.push_back(i);
    }


    for ( const auto & i : b_moves.moves) {
        moves_pos.push_back(i);
    }
    for ( const auto & i : b_moves.captures) {
        moves_pos.push_back(i);
    }

    for ( const auto & i : b_moves.moves_sections) {
        moves_sections.push_back(i);
    }
    for ( const auto & i : b_moves.captures_section_mask) {
        captures_mask.push_back(i);
    }



    auto moves = Moves(moves_pos,captures,moves_sections,captures_mask);
    return moves;
}


Moves king_moves(const Board& board, const Piece& chosen_piece) {
    std::vector<Position> moves_pos;
    std::vector<Position> captures;
    Position next_position = chosen_piece.position;

    std::vector<int> captures_mask;
    std::vector<std::vector<Position>> moves_sections;

    bool inside = true;
    bool occupied = true;
    bool capture = false;

    const std::vector<std::vector<int>> move_king = {{0,1},  {0,-1},  {-1,0}, {1,0},  {1,1},  {1,-1},  {-1,1}, {-1,-1}};

    const Player *p = nullptr;
    const Player *p2 = nullptr;

    //TODO if order change in initialization this brokes
    if (chosen_piece.color == "white") {
        p = &board.players[0];
        p2 = &board.players[1];
    }
    else {
        p = &board.players[1];
        p2 = &board.players[0];
    }

    bool free_tile = true;
    int count_attacked = 0;
    int free_tile_c = 0;



    for (const auto & i : move_king) {
        next_position.x += i[0];
        next_position.y += i[1];
        inside = next_position.inside();
        occupied = check_occupied(board,next_position);
        capture = check_move(board,next_position,chosen_piece.color);

        const std::vector<std::vector<int>> move_pawn_white = {{0,1},  {1,1},  {-1,1} };
        const std::vector<std::vector<int>> move_pawn_black = {{0,-1},  {1,-1},  {-1,-1}};
        const std::vector<std::vector<int>> *move_pawn = nullptr;
        //first do not move where other are
        bool attacked = false;
        for (const auto & piece : p2->pieces) {
            if (piece.name == "Pawn") {

                if (chosen_piece.color == "white") {
                    move_pawn = &move_pawn_black;
                }
                else if (chosen_piece.color == "black") {
                    move_pawn = &move_pawn_white;
                }
                if (piece.position.x + (*move_pawn)[1][0] == next_position.x && piece.position.y + (*move_pawn)[1][1]== next_position.y) {
                    attacked = true;
                    std::cout << "attacked by pawn" << std::endl;
                    break;
                }
                if (piece.position.x + (*move_pawn)[2][0] == next_position.x && piece.position.y + (*move_pawn)[2][1]== next_position.y) {
                    attacked = true;
                    std::cout << "attacked by pawn" << std::endl;
                    break;
                }
                continue;
            }
            for (const auto & move : piece.moves_history) {
                for (const auto & k : move.moves) {
                    if (k.x == next_position.x && k.y == next_position.y) {
                        attacked = true;
                        break;
                    }
                }


            }
        }
        if (attacked) {
            std::cout << "attacked" << std::endl;
        }
        //free tile
        if (inside && !occupied && !capture && !attacked) {
            free_tile_c++;
            moves_pos.push_back(next_position);
        }

        else if (inside && occupied && !attacked && capture) {
            captures.push_back(next_position);
        }

        next_position = chosen_piece.position;
    }
    if (free_tile_c == count_attacked) {

    }
    auto moves = Moves(moves_pos,captures,moves_sections,captures_mask);
    return moves;
}

