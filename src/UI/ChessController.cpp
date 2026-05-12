#include "ChessController.h"
#include "engine/engine.h"
#include "iostream"

ChessController::ChessController(QObject *parent) : QObject(parent) {
    // backendGame = new Core::Game();

    board.initialize();
}

bool ChessController::isValidMove(ChessPiece* piece, int fromCol, int fromRow, int toCol, int toRow) {
    // if the user places a pice to the same square
    if (fromCol == toCol && fromRow == toRow) {
        return false;
    }
    std::cout << "Generating moves" << std::endl;
    for(auto& p : board.players[0].pieces) {
        std::cout << "Generate move" << std::endl;
        p.move(board);
    }
    std::cout << "Moves generated" << std::endl;
    /*for(auto p : board.players[1].pieces) {
        p.move(board);
    }*/

    // bool isValid = backendGame->validate_move(fromSquare.toStdString(), toSquare.toStdString());
    bool isValid = true;

    if (isValid) {
        qDebug() << "[Controller] Valid move: " << fromCol << fromRow << "->" << toCol << toRow;
        // backendGame->make_move(
        
    } else {
        qDebug() << "[Controller] Invalid move: " << fromCol << fromRow << "->" << toCol << toRow;
    }

    return isValid;
}