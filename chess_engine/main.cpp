#include <iostream>
#include <vector>
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.

class Board {


    std::vector<std::vector<int>> board;
    std::vector<std::vector<int>> free_spaces;
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

    static void print_position(){}
    Position get_position() const { return Position(x, y); }
};

class Horse {
    int x;
    int y;
    const std::vector<std::vector<int>> moves = {{2,1},  {2,-1},  {-2,1}, {-2,-1}, {1, 2}, {-1,2},{-1, -2}, {1,-2}  };

    Horse(const int x, const int y) : x(x), y(y) {}

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
