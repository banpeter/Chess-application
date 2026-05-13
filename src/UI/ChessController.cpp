#include "ChessController.h"
#include "engine/engine.h"
#include "iostream"

#define CALIB 7
ChessController::ChessController(QObject *parent) : QObject(parent) {
    // backendGame = new Core::Game();

    board.initialize();
}

bool ChessController::isValidMove(ChessPiece* piece, int fromCol, int fromRow, int toCol, int toRow) {
    // if the user places a pice to the same square
    fromRow = CALIB - fromRow;
    toRow = CALIB - toRow;
    if (fromCol == toCol && fromRow == toRow) {
        return false;
    }
    std::cout << "Generating moves" << std::endl;
    for(auto& p : board.players[0].pieces) {
        //std::cout << "Generate move" << std::endl;
        p.move(board);
    }
    std::cout << "Moves generated" << std::endl;
    //check valid move
    //TODO create Position from the int values
    Position current_position = Position(fromCol, fromRow);
    Position next_position = Position(toCol, toRow);
    //bool isValid = validate_move( board,  current_position,  next_position, color, piece_name) ;
    //bool isValid = true;

    //apply move
    std::string pieceName = "";
    if (piece->getPieceType() == PieceType::Pawn) {
        pieceName = "Pawn";
    }
    else if (piece->getPieceType() == PieceType::Knight) {
        pieceName = "Knight";
    }
    else if (piece->getPieceType() == PieceType::Bishop) {
        pieceName = "Bishop";
    }
    else if (piece->getPieceType() == PieceType::Rook) {
        pieceName = "Rook";
    }
    else if (piece->getPieceType() == PieceType::Queen) {
        pieceName = "Queen";
    }
    else if (piece->getPieceType() == PieceType::King) {
        pieceName = "King";
    }

    //validates. If valid apply, otherwise do not do anything
    bool isValid = board.players[0].apply_move( pieceName, current_position, next_position, board.players[1]);
    //TODO test
    //TODO MinMAX


    // bool isValid = backendGame->validate_move(fromSquare.toStdString(), toSquare.toStdString());


    if (isValid) {
        qDebug() << "[Controller] Valid move: " << fromCol << fromRow << "->" << toCol << toRow;
        // backendGame->make_move(

    } else {
        qDebug() << "[Controller] Invalid move: " << fromCol << fromRow << "->" << toCol << toRow;
    }

    return isValid;
}