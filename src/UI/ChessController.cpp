#include "ChessController.h"

ChessController::ChessController(QObject *parent) : QObject(parent) {
    // engine initialization
}

bool ChessController::isValidMove(int fromCol, int fromRow, int toCol, int toRow) {
    // if the user places a pice to the same square
    if (fromCol == toCol && fromRow == toRow) {
        return false;
    }

    // bool isValid = 
    bool isValid = true;

    if (isValid) {
        qDebug() << "[Controller] Valid move: " << fromCol << fromRow << "->" << toCol << toRow;
        
    } else {
        qDebug() << "[Controller] Invalid move: " << fromCol << fromRow << "->" << toCol << toRow;
        return false;
    }

    return isValid;
}

void ChessController::triggerEngineMove() {
    QTimer::singleShot(1000, this, [this]() {
        
        
        //dummy move
        int fromCol = 1; 
        int fromRow = 0; 
        int toCol = 2;   
        int toRow = 2;   

        qDebug() << "[Engine] move: " << fromCol << fromRow << " -> " << toCol << toRow;

        emit movePieceCommand(fromCol, fromRow, toCol, toRow);
    });
}