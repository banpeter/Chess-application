#include <iostream>
#include <vector>
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.

class Board {


    std::vector<std::vector<int>> board;
    std::vector<std::vector<int>> free_spaces;

    //get valid moves, base on piece postions validate correct ones
};




class Position {
    public:
        int x, y;

    Position(const int x, const int y) : x(x), y(y) {}



    void print() const { std::cout << x << " " << y << std::endl; }

};


class GamedInitialization {
    std::vector<std::vector<int>> moves = {{1, 2}, {-1,2}, {2,1},  {-2,1}  };


    static void pieceInitialization(const std::vector<Position>& pos) {
        for (int i = 0; i < pos.size(); ++i) {}
    }

};


class Piece {
    public:
        int x, y;
        Position position;
        std::string name;
        const std::vector<std::vector<int>> moves;
        Piece(const int x, const int y) : x(x), y(y), position(x,y) {
            }

        static void print_position(){}
        Position get_position() const { return Position(x, y); }
        std::vector<std::vector<Position>> get_valid_moves() const {}

        void set_position(const Position& pos) { x=pos.x; y=pos.y; }

};

class Player {
public:
    std::string name;
    std::string color;
    std::vector<std::vector<Piece>> pieces_pawns;
    std::vector<std::vector<Piece>> pieces;
    static void print_pieces(){}
    std::vector<std::vector<Position>> get_positions() const {}
};


class Knight {
    int x;
    int y;
    const std::vector<std::vector<int>> moves = {{2,1},  {2,-1},  {-2,1}, {-2,-1}, {1, 2}, {-1,2},{-1, -2}, {1,-2}  };

    Knight(const int x, const int y) : x(x), y(y) {}

    //for example the position change of the rook is based on the intou
    static void change_position(const int x, const int y) {}

    static void show_piece_name() { std::cout << "Value: " << "Horse" << std::endl;}
};

class Bishop {
    int x;
    int y;
    const std::vector<std::vector<int>> moves = {{2,1},  {2,-1},  {-2,1}, {-2,-1}, {1, 2}, {-1,2},{-1, -2}, {1,-2}  };

    Bishop(const int x, const int y) : x(x), y(y) {}

    //for example the position change of the rook is based on the intou
    static void change_position(const int x, const int y) {}

    static void show_piece_name() { std::cout << "Value: " << "Horse" << std::endl;}
};



class Rook {
    int x;
    int y;
    const std::vector<std::vector<int>> moves = {{2,1},  {2,-1},  {-2,1}, {-2,-1}, {1, 2}, {-1,2},{-1, -2}, {1,-2}  };

    Rook(const int x, const int y) : x(x), y(y) {}

    //for example the position change of the rook is based on the intou
    static void change_position(const int x, const int y) {}

    static void show_piece_name() { std::cout << "Value: " << "Horse" << std::endl;}
};


class King {
    int x;
    int y;
    const std::vector<std::vector<int>> moves = {{2,1},  {2,-1},  {-2,1}, {-2,-1}, {1, 2}, {-1,2},{-1, -2}, {1,-2}  };

    King(const int x, const int y) : x(x), y(y) {}

    //for example the position change of the rook is based on the intou
    static void change_position(const int x, const int y) {}

    static void show_piece_name() { std::cout << "Value: " << "Horse" << std::endl;}
};


class Queen {
    int x;
    int y;
    const std::vector<std::vector<int>> moves = {{2,1},  {2,-1},  {-2,1}, {-2,-1}, {1, 2}, {-1,2},{-1, -2}, {1,-2}  };

    Queen(const int x, const int y) : x(x), y(y) {}

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


int main() {
    // TIP Press <shortcut actionId="RenameElement"/> when your caret is at the <b>lang</b> variable name to see how CLion can help you rename it.
    auto lang = "C++";
    std::cout << "Hello and welcome to " << lang << "!\n";

    for (int i = 1; i <= 5; i++) {
        // TIP Press <shortcut actionId="Debug"/> to start debugging your code. We have set one <icon src="AllIcons.Debugger.Db_set_breakpoint"/> breakpoint for you, but you can always add more by pressing <shortcut actionId="ToggleLineBreakpoint"/>.
        std::cout << "i = " << i << std::endl;
    }

    return 0;
    // TIP See CLion help at <a href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>. Also, you can try interactive lessons for CLion by selecting 'Help | Learn IDE Features' from the main menu.
}
