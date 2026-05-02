#include <iostream>
#include <vector>
#include "engine.h"

//TODO check for attacked tiles
//TODO if kning_moves is all attacked game voer



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

    bool end = false;

    while (!end) {
        for(auto p : board.players[0].pieces) {
            p.move(board);
        }
        for(auto p : board.players[1].pieces) {
            p.move(board);
        }
        end = true;
    }

    //for loop to step each piece


    MoveFunction rook_moves_generation = rook_moves;
    MoveFunction bishop_moves_generation = bishop_moves;
    MoveFunction knight_moves_generation = knight_moves;

    return 0;
    // TIP See CLion help at <a href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>. Also, you can try interactive lessons for CLion by selecting 'Help | Learn IDE Features' from the main menu.
}
