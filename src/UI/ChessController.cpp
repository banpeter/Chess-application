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
    
int counter = 0;
void ChessController::triggerEngineMove() {
    // Dummy engine move


    if (counter == 0) {
        emit engineMoved(0, 1, 0, 3);
        counter++;
    } else if (counter == 1) {
        emit engineMoved(4, 1, 4, 3, "queen");
        counter++;
    } else {
        emit engineMoved(1, 0, 2, 2);
    }

}


bool ChessController::isCheckmate(PieceColor color) {
    // dummy checkmate detection
    return true;
}

void ChessController::promotePawnToEngine(int col, int row, PieceColor color, PieceType selectedType) {
    
    // this method informs the engine about the promotion, so it can update its internal board
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