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
        qDebug() << "[Controller] valid move: " << fromCol << fromRow << "->" << toCol << toRow;
        
    } else {
        qDebug() << "[Controller] invalid move: " << fromCol << fromRow << "->" << toCol << toRow;
        return false;
    }

    return isValid;
}

void ChessController::triggerEngineMove() {
        
        //dummy move
        int fromCol = 1; 
        int fromRow = 0; 
        int toCol = 2;   
        int toRow = 2;   

        qDebug() << "[Engine] move: " << fromCol << fromRow << " -> " << toCol << toRow;

        emit movePieceCommand(fromCol, fromRow, toCol, toRow);
}

QString ChessController::pieceTypeToString(PieceType type) {
    switch (type) {
        case PieceType::Pawn: return "pawn";
        case PieceType::Rook: return "rook";
        case PieceType::Knight: return "knight";
        case PieceType::Bishop: return "bishop";
        case PieceType::Queen: return "queen";
        case PieceType::King: return "king";
        default: return "";
    }
}

QString ChessController::pieceColorToString(PieceColor color) {
    switch (color) {
        case PieceColor::White: return "white";
        case PieceColor::Black: return "black";
        default: return "";
    }
}