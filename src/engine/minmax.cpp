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


int minimax(Board board,int depth, int alpha, int beta,bool is_maximizing, unsigned int index, unsigned int index2) {

    if (depth >= 5) {
        return evaluate(board,index,index2);
    }

    bool end_game = false;
    bool is_cheked = false;
    for (auto piece : board.players[0].pieces) {
        if (piece.name == "King") {
            end_game = check_mate(board, piece);
            is_cheked = check(board,piece);
            break;
        }
    }
    if (end_game) {
        return evaluate(board,index,index2);
    }
    //mert ha már sakban volt és az új lépés után is sakban van nem jó a lépés -> invalid
    if (board.players[index].is_checked && is_cheked) {
        return -1;
    }
    //if min checked me generae board. Where in new board still checked leav it out


    unsigned int ind = index;
    index = index2;
    index2 = ind;
    if (is_maximizing) {
        index = 0;
        index2 = 1;
    }
    else {
        index = 1;
        index2 = 0;
    }



    std::vector<Moves> possible_moves;
    std::vector<std::string> piece_names;
    std::vector<Board> possible_boards;

    //for each move create updated board

    //generate_moves
    for(auto p : board.players[index].pieces) {
        auto move = p.move(board);
        possible_moves.push_back(move);
        piece_names.push_back(p.name);
    }
    //APPLY moves -> possible boards
    for (int i = 0; i < possible_moves.size(); i++) {
        for (int j = 0; j < possible_moves[i].moves.size(); j++) {
            Board pboard= apply_move(board,piece_names[i],possible_moves[i].moves[j],index,index2);
            //std::cout << piece_names[i] << std::endl;
            if (index == 0) {

                if (piece_names[i] == "Pawn" && possible_moves[i].moves[j].y == 7) {
                    Board pboard_queen= apply_move(board,piece_names[i],possible_moves[i].moves[j],index,index2);
                    Board pboard_rook= apply_move(board,piece_names[i],possible_moves[i].moves[j],index,index2);
                    Board pboard_knight= apply_move(board,piece_names[i],possible_moves[i].moves[j],index,index2);
                    Board pboard_bishop= apply_move(board,piece_names[i],possible_moves[i].moves[j],index,index2);


                    promote_pawn(pboard_queen,  possible_moves[i].moves[j], "Queen", "white");
                    promote_pawn(pboard_rook,  possible_moves[i].moves[j], "Rook", "white");
                    promote_pawn(pboard_knight,  possible_moves[i].moves[j], "Knight", "white");
                    promote_pawn(pboard_bishop,  possible_moves[i].moves[j], "Bishop", "white");

                    possible_boards.push_back(pboard_queen);
                    possible_boards.push_back(pboard_rook);
                    possible_boards.push_back(pboard_knight);
                    possible_boards.push_back(pboard_bishop);
                }
            }
            else {
                if (piece_names[i] == "Pawn" && possible_moves[i].moves[j].y == 0) {
                    Board pboard_queen= apply_move(board,piece_names[i],possible_moves[i].moves[j],index,index2);
                    Board pboard_rook= apply_move(board,piece_names[i],possible_moves[i].moves[j],index,index2);
                    Board pboard_knight= apply_move(board,piece_names[i],possible_moves[i].moves[j],index,index2);
                    Board pboard_bishop= apply_move(board,piece_names[i],possible_moves[i].moves[j],index,index2);
                    //call promote for each piecetype to get a new board

                    promote_pawn(pboard_queen,  possible_moves[i].moves[j], "Queen", "black");
                    promote_pawn(pboard_rook,  possible_moves[i].moves[j], "Rook", "black");
                    promote_pawn(pboard_knight,  possible_moves[i].moves[j], "Knight", "black");
                    promote_pawn(pboard_bishop,  possible_moves[i].moves[j], "Bishop", "black");

                    possible_boards.push_back(pboard_queen);
                    possible_boards.push_back(pboard_rook);
                    possible_boards.push_back(pboard_knight);
                    possible_boards.push_back(pboard_bishop);
                }

            }
            //check for check and checkmate

            possible_boards.push_back(pboard);
        }
        for (int j = 0; j < possible_moves[i].captures.size(); j++) {
            Board pboard= apply_move(board,piece_names[i],possible_moves[i].captures[j],index,index2);
                        if (index == 0) {

                if (piece_names[i] == "Pawn" && possible_moves[i].captures[j].y == 7) {
                    Board pboard_queen= apply_move(board,piece_names[i],possible_moves[i].captures[j],index,index2);
                    Board pboard_rook= apply_move(board,piece_names[i],possible_moves[i].captures[j],index,index2);
                    Board pboard_knight= apply_move(board,piece_names[i],possible_moves[i].captures[j],index,index2);
                    Board pboard_bishop= apply_move(board,piece_names[i],possible_moves[i].captures[j],index,index2);
                    //call promote for each piecetype to get a new board

                    promote_pawn(pboard_queen,  possible_moves[i].captures[j], "Queen", "white");
                    promote_pawn(pboard_rook,  possible_moves[i].captures[j], "Rook", "white");
                    promote_pawn(pboard_knight,  possible_moves[i].captures[j], "Knight", "white");
                    promote_pawn(pboard_bishop,  possible_moves[i].captures[j], "Bishop", "white");

                    possible_boards.push_back(pboard_queen);
                    possible_boards.push_back(pboard_rook);
                    possible_boards.push_back(pboard_knight);
                    possible_boards.push_back(pboard_bishop);
                }
            }
            else {
                if (piece_names[i] == "Pawn" && possible_moves[i].captures[j].y == 0) {
                    Board pboard_queen= apply_move(board,piece_names[i],possible_moves[i].captures[j],index,index2);
                    Board pboard_rook= apply_move(board,piece_names[i],possible_moves[i].captures[j],index,index2);
                    Board pboard_knight= apply_move(board,piece_names[i],possible_moves[i].captures[j],index,index2);
                    Board pboard_bishop= apply_move(board,piece_names[i],possible_moves[i].captures[j],index,index2);
                    //call promote for each piecetype to get a new board

                    promote_pawn(pboard_queen,  possible_moves[i].captures[j], "Queen", "black");
                    promote_pawn(pboard_rook,  possible_moves[i].captures[j], "Rook", "black");
                    promote_pawn(pboard_knight,  possible_moves[i].captures[j], "Knight", "black");
                    promote_pawn(pboard_bishop,  possible_moves[i].captures[j], "Bishop", "black");

                    possible_boards.push_back(pboard_queen);
                    possible_boards.push_back(pboard_rook);
                    possible_boards.push_back(pboard_knight);
                    possible_boards.push_back(pboard_bishop);
                }
            }

            possible_boards.push_back(pboard);

        }

    }



    if (is_maximizing) {
        int best = std::numeric_limits<int>::min();

        for (const Board& child : possible_boards) {
            int score = minimax(child, depth + 1, alpha, beta, false, index,  index2);
            best  = std::max(best, score);
            alpha = std::max(alpha, best);

            if (beta <= alpha)
                break;
        }
        return best;

    } else {
        int best = std::numeric_limits<int>::max();

        for (const Board& child : possible_boards) {
            int score = minimax(child, depth + 1, alpha, beta, true,   index,   index2);
            best = std::min(best, score);
            beta = std::min(beta, best);

            if (beta <= alpha)
                break;
        }
        return best;
    }

}


// Find the best move from root
//TODO return position
PosChange best_move(Board& root, int depth, std::string color, int which_player) {
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

    std::vector<Moves> possible_moves;
    std::vector<std::string> piece_names;
    std::vector<Board> possible_boards;

    Position current_position = Position(-1, -1);
    Position next_position = Position(-1, -1);
    std::string pieceName;
    int score = 0;

    for(auto& p : root.players[1].pieces) {
        p.move(root);
    }
    std::cout<<"startminax"<<std::endl;
    for(auto& p : root.players[1].pieces) {
        std::cout<<"piece chosen"<<std::endl;
        for (const auto & move : p.moves_history) {
            if (!p.moves_history.empty() && !p.moves_history.back().moves.empty()) {
                for (const auto & k : move.moves) {
                    Board pboard= apply_move(root,p.name,k,index,index2);
                    score = minimax(pboard, depth + 1, alpha, beta, false, index, index2);
                    if (score >= best_score) {
                        best_score = score;
                        current_position.x = p.position.x;
                        current_position.y = p.position.y;
                        next_position.x = k.x;
                        next_position.y =k.y;
                        pieceName = p.name;

                    }
                }
            }

        }
    }

    bool isValid =  root.players[1].apply_move(root, pieceName, current_position, next_position, root.players[0]);

    //for loop for the first move

    PosChange poschange = {current_position, next_position};
    std::cout<<"poschange"<<std::endl;
    std::cout<< isValid <<std::endl;
    std::cout<<"poschange" << current_position.x << " " << current_position.y <<std::endl;
    std::cout<<"poschange" << next_position.x << " " << next_position.y <<std::endl;
    return poschange;
}