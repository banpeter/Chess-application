#include <iostream>
#include <vector>
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.



class Position {
public:
    int x, y;

    Position(const int x, const int y) : x(x), y(y) {}
    void print() const { std::cout << x << " " << y << std::endl; }
    bool upgrade(const std::string& color, const std::string& name) {

        if (color == "white" && name == "pawn" && y == 8) {
            return true;
            //std::cout << "White" << std::endl;
        }
        if (color == "black" && name == "pawn" && y == 0) {
            return true;
            //std::cout << "Black" << std::endl;
        }


        return false;
    }
    bool inside() {

        if (x >= 0 && x <= 8 && y >= 0 && y <= 8) {
            return true;
        }
        return false;
    }
};

class Moves {
    public:
    std::vector<Position> moves;
    std::vector<Position> captures;
    Moves(const std::vector<Position>& moves, const std::vector<Position>& captures) : moves(moves), captures(captures) {}

};

class Board;
//TODO castle and double at generating moves, and upgrade as well
using MoveFunction = Moves(*)(const Board&, Position);

class Piece {
public:
    Position position;
    const std::string name;
    MoveFunction rook_moves_generation;
    bool moved = false;
    const std::vector<std::vector<int>> moves;
    Piece(const std::string& name, const Position position) : position(position), name(name) {
    }

    static void print_position(){}
    Position get_position() const { return position; }
    std::vector<std::vector<Position>> get_valid_moves() const {}

    void set_position(const Position& pos) { position.x=pos.x; position.y=pos.y; }

};

class Player {
public:
    std::string name;
    std::string color;
    std::vector<Piece> pieces_pawns;
    std::vector<Piece> pieces;
    Player(const std::string& name, const std::string color) :  name(name), color(color) {
    }
    static void print_pieces(){}


    std::vector<std::vector<Position>> get_positions() const {}

    void init_pieces() {

        int y = 1;
        if (color == "white") {
            y = 1;
            pieces.push_back(Piece("King", Position(4,0)));
            pieces.push_back(Piece("Queen", Position(5,0)));

            pieces.push_back(Piece("Rook", Position(0,0)));
            pieces.push_back(Piece("Knight", Position(1,0)));
            pieces.push_back(Piece("Bishop", Position(3,0)));

            pieces.push_back(Piece("Rook", Position(8,0)));
            pieces.push_back(Piece("Knight", Position(7,0)));
            pieces.push_back(Piece("Bishop", Position(6,0)));
        }
        else if (color == "black") {
            y = 7;
            pieces.push_back(Piece("King", Position(4,8)));
            pieces.push_back(Piece("Queen", Position(5,8)));

            pieces.push_back(Piece("Rook", Position(0,8)));
            pieces.push_back(Piece("Knight", Position(1,8)));
            pieces.push_back(Piece("Bishop", Position(3,8)));

            pieces.push_back(Piece("Rook", Position(8,8)));
            pieces.push_back(Piece("Knight", Position(7,8)));
            pieces.push_back(Piece("Bishop", Position(6,8)));
        }
        std::cout << "Adding pawns" << std::endl;

        for (int i = 0; i < 8; i++) {
            pieces_pawns.push_back(Piece(color, Position(i,y)));
        }





    }
};


class Board {

    public:
        std::vector<std::vector<int>> board;
        std::vector<std::vector<int>> free_spaces;
        std::vector<Player> players;

        const int min_x = 0;
        const int min_y = 0;
        const int max_x = 8;
        const int max_y = 8;

        const int number_of_players = 2;



        void print() const {}


        void initialize() {
            players.push_back(Player("Player 1" , "white"));
            players.push_back(Player("Player 2","black"));

            for ( auto& player : players) {
                player.init_pieces();
            }
        }

    //get valid moves, base on piece postions validate correct ones
};


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


Moves rook_moves(const Board& board, Position current_position_of_chosen_piece) {
    std::vector<Position> moves_pos;
    std::vector<Position> captures;
    Position next_position = current_position_of_chosen_piece;
    bool inside = true;
    bool capture = false;

    bool generate = true;

    for (int i = 0; i < 4; i++) {
        while (generate) {
            next_position.x++;
            //check inside
            inside = next_position.inside();
            capture = check_move(board,current_position_of_chosen_piece);//TODO

            if (inside && !capture) {
                moves_pos.push_back(next_position);
            }
            else if (inside && capture) {
                captures.push_back(next_position);
                generate = false;
            }
            else if (!inside) {
                generate = false;
            }

        }
        next_position = current_position_of_chosen_piece;
        while (next_position.inside()) {
            next_position.x--;
            inside = next_position.inside();
            capture = check_move(board,current_position_of_chosen_piece);//TODO

            if (inside && !capture) {
                moves_pos.push_back(next_position);
            }
            else if (inside && capture) {
                captures.push_back(next_position);
                generate = false;
            }
            else if (!inside) {
                generate = false;
            }
        }
        next_position = current_position_of_chosen_piece;
        while (next_position.inside()) {
            next_position.y++;
            inside = next_position.inside();
            capture = check_move(board,current_position_of_chosen_piece);//TODO

            if (inside && !capture) {
                moves_pos.push_back(next_position);
            }
            else if (inside && capture) {
                captures.push_back(next_position);
                generate = false;
            }
            else if (!inside) {
                generate = false;
            }
        }
        next_position = current_position_of_chosen_piece;
        while (next_position.inside()) {
            next_position.y--;
            inside = next_position.inside();
            capture = check_move(board,current_position_of_chosen_piece);//TODO

            if (inside && !capture) {
                moves_pos.push_back(next_position);
            }
            else if (inside && capture) {
                captures.push_back(next_position);
                generate = false;
            }
            else if (!inside) {
                generate = false;
            }
        }
    }

    auto moves = Moves(moves_pos,captures);
    return moves;
}

Moves bishop_moves(const Board& board, Position current_position_of_chosen_piece) {
    std::vector<Position> moves_pos;
    std::vector<Position> captures;
    Position next_position = current_position_of_chosen_piece;
    bool inside = true;
    bool capture = false;

    bool generate = true;

    for (int i = 0; i < 4; i++) {
        while (generate) {
            next_position.x++;
            next_position.y++;
            //check inside
            inside = next_position.inside();
            capture = check_move(board,current_position_of_chosen_piece);//TODO

            if (inside && !capture) {
                moves_pos.push_back(next_position);
            }
            else if (inside && capture) {
                captures.push_back(next_position);
                generate = false;
            }
            else if (!inside) {
                generate = false;
            }

        }
        next_position = current_position_of_chosen_piece;
        while (next_position.inside()) {
            next_position.x--;
            next_position.y--;
            inside = next_position.inside();
            capture = check_move(board,current_position_of_chosen_piece);//TODO

            if (inside && !capture) {
                moves_pos.push_back(next_position);
            }
            else if (inside && capture) {
                captures.push_back(next_position);
                generate = false;
            }
            else if (!inside) {
                generate = false;
            }
        }
        next_position = current_position_of_chosen_piece;
        while (next_position.inside()) {
            next_position.x--;
            next_position.y++;
            inside = next_position.inside();
            capture = check_move(board,current_position_of_chosen_piece);//TODO

            if (inside && !capture) {
                moves_pos.push_back(next_position);
            }
            else if (inside && capture) {
                captures.push_back(next_position);
                generate = false;
            }
            else if (!inside) {
                generate = false;
            }
        }
        next_position = current_position_of_chosen_piece;
        while (next_position.inside()) {
            next_position.x++;
            next_position.y--;
            inside = next_position.inside();
            capture = check_move(board,current_position_of_chosen_piece);//TODO

            if (inside && !capture) {
                moves_pos.push_back(next_position);
            }
            else if (inside && capture) {
                captures.push_back(next_position);
                generate = false;
            }
            else if (!inside) {
                generate = false;
            }
        }
    }

    auto moves = Moves(moves_pos,captures);
    return moves;
}

Moves knight_moves(const Board& board, Position current_position_of_chosen_piece) {
    std::vector<Position> moves_pos;
    std::vector<Position> captures;
    Position next_position = current_position_of_chosen_piece;
    bool inside = true;
    bool capture = false;

    const std::vector<std::vector<int>> move_knight = {{2,1},  {2,-1},  {-2,1}, {-2,-1}, {1, 2}, {-1,2},{-1, -2}, {1,-2}  };

    for (auto& move : move_knight) {
        next_position.x += move[0];
        next_position.y += move[1];
        inside = next_position.inside();
        capture = check_move(board,current_position_of_chosen_piece);
        if (inside && !capture) {
            moves_pos.push_back(next_position);
        }
        else if (inside && capture) {
            captures.push_back(next_position);
        }
        next_position = current_position_of_chosen_piece;
    }
    auto moves = Moves(moves_pos,captures);
    return moves;
}

Moves pawn_moves(const Board& board, Position current_position_of_chosen_piece) {
    std::vector<Position> moves_pos;
    std::vector<Position> captures;
    Position next_position = current_position_of_chosen_piece;
    bool inside = true;
    bool capture = false;

    const std::vector<std::vector<int>> pawn_knight = {{0,1},  {1,1},  {-1,-1},  {0, 2} };

    for (auto& move : pawn_knight) {
        next_position.x += move[0];
        next_position.y += move[1];
        inside = next_position.inside();
        capture = check_move(board,current_position_of_chosen_piece);
        if (inside && !capture) {
            moves_pos.push_back(next_position);
        }
        else if (inside && capture) {
            captures.push_back(next_position);
        }
        next_position = current_position_of_chosen_piece;
    }
    auto moves = Moves(moves_pos,captures);
    return moves;
}

//TODO check for capturing

class GamedInitialization {

    std::vector<std::vector<int>> moves_knight = {{1, 2}, {-1,2}, {2,1},  {-2,1}  };

    std::vector<std::vector<int>> moves_pawn = {{1, 2}, {-1,2}, {2,1},  {-2,1}  };
    std::vector<std::vector<int>> moves_king = {{1, 2}, {-1,2}, {2,1},  {-2,1}  };
    std::vector<std::vector<int>> moves_queen= {{1, 2}, {-1,2}, {2,1},  {-2,1}  };



    static void pieceInitialization(const std::vector<Position>& pos) {
        for (int i = 0; i < pos.size(); ++i) {}
    }

};

void game_loop(Board board) {

    bool check_mate = false;

    while (!check_mate) {

    }
}



class Knight {
    int x;
    int y;
    const std::vector<std::vector<int>> moves = {{2,1},  {2,-1},  {-2,1}, {-2,-1}, {1, 2}, {-1,2},{-1, -2}, {1,-2}  };

    Knight(const int x, const int y) : x(x), y(y) {}

    //for example the position change of the rook is based on the intou
    static void change_position(const int x, const int y) {}

    static void show_piece_name() { std::cout << "Value: " << "Horse" << std::endl;}
};


class Pawn {
    int x;
    int y;
    bool special_available = true;
    std::vector<int> special_move;
    const std::vector<std::vector<int>> moves = {{0,1} };

    Pawn(const int x, const int y) : x(x), y(y) {}

    //for example the position change of the rook is based on the intou
    static void change_position(const int x, const int y) {}

    static void show_piece_name() { std::cout << "Value: " << "Horse" << std::endl;}
};

/*
 * TODO list
 *
 * Initialize game
 * Initilaize players
 * Initilize pieces
 *
 */
int main() {
    // TIP Press <shortcut actionId="RenameElement"/> when your caret is at the <b>lang</b> variable name to see how CLion can help you rename it.
    auto lang = "C++";
    std::cout << "Hello and welcome to " << lang << "!\n";

    for (int i = 1; i <= 5; i++) {
        // TIP Press <shortcut actionId="Debug"/> to start debugging your code. We have set one <icon src="AllIcons.Debugger.Db_set_breakpoint"/> breakpoint for you, but you can always add more by pressing <shortcut actionId="ToggleLineBreakpoint"/>.
        std::cout << "i = " << i << std::endl;
    }

    auto board = Board();
    board.initialize();

    MoveFunction rook_moves_generation = rook_moves;
    MoveFunction bishop_moves_generation = bishop_moves;
    MoveFunction knight_moves_generation = knight_moves;

    return 0;
    // TIP See CLion help at <a href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>. Also, you can try interactive lessons for CLion by selecting 'Help | Learn IDE Features' from the main menu.
}
