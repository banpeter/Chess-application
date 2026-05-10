#include "ChessController.h"

ChessController::ChessController(QObject *parent) : QObject(parent) {
    // backendGame = new Core::Game();
}

bool ChessController::isValidMove(ChessPiece* piece, int fromCol, int fromRow, int toCol, int toRow) {
    // if the user places a pice to the same square
    if (fromCol == toCol && fromRow == toRow) {
        return false;
    }

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