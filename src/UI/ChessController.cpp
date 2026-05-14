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
    bool isValid = board.players[0].apply_move(board, pieceName, current_position, next_position, board.players[1]);
    //check for checkmate
    std::cout << "Moves generated " << isValid << std::endl;
    bool end_game = false;
    bool is_cheked = false;
    for (auto piece : board.players[0].pieces) {
        if (piece.name == "King") {
           end_game = check_mate(board, piece);
           is_cheked = check(board,piece);
            break;
        }
    }
    if (is_cheked) {
        board.players[1].is_checked = true;
    }


    //Run AI move -> check for check mate -> check if it checked the player, If yes bool_is chcecked set true for the player.

    //is check given to the other player. If yes bool_is chcecked set true for the other player.

    //TODO check for checkmate and check if valid
    //TODO MinMAX
    //modify board and return position to update
    //PosChange change_position =  best_move(board, 0, "white",0);


    // bool isValid = backendGame->validate_move(fromSquare.toStdString(), toSquare.toStdString());


    if (isValid) {
        qDebug() << "[Controller] Valid move: " << fromCol << fromRow << "->" << toCol << toRow;
        // backendGame->make_move(

    } else {
        qDebug() << "[Controller] Invalid move: " << fromCol << fromRow << "->" << toCol << toRow;
    }

    return isValid;
}


std::string convert(PieceType selectedType) {
    std::string pieceName = "";
    if (selectedType == PieceType::Pawn) {
        pieceName = "Pawn";
    }
    else if (selectedType == PieceType::Knight) {
        pieceName = "Knight";
    }
    else if (selectedType == PieceType::Bishop) {
        pieceName = "Bishop";
    }
    else if (selectedType == PieceType::Rook) {
        pieceName = "Rook";
    }
    else if (selectedType == PieceType::Queen) {
        pieceName = "Queen";
    }
    else if (selectedType == PieceType::King) {
        pieceName = "King";
    }
    return pieceName;
}

void ChessController::promotePawnToEngine(int col, int row, PieceColor color, PieceType selectedType) {
    std::string scolor = "white"; //the user is always white
    std::string ptype = convert(selectedType);
    Position current_position = Position(col, row);
    promote_pawn(board,  current_position, ptype, scolor);
    //TODO check for checkmate and check

    // this method informs the engine about the promotion, so it can update its internal board
}

void ChessController::triggerEngineMove() {
    // Dummy engine move



    PosChange change_position =  best_move(board, 0, "black",0);

    std::cout << change_position.prev.x << std::endl;
    emit movePieceCommand(change_position.prev.x, CALIB-change_position.prev.y, change_position.current.x, CALIB-change_position.current.y, ""); //alapból üres, ha átváltozás van beírni mit



}