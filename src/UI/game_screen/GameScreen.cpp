#include "GameScreen.h"
#include "ChessPiece.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QColor>
#include <QMessageBox>

GameScreen::GameScreen(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // top bar
    QHBoxLayout *topBarLayout = new QHBoxLayout();
    backButton = new QPushButton("Back to menu", this);
    backButton->setMinimumHeight(30);
    
    topBarLayout->addWidget(backButton);
    topBarLayout->addStretch(); 


    // chess board
    boardScene = new QGraphicsScene(this);
    boardView = new QGraphicsView(boardScene, this);
    
    boardView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    boardView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    boardView->setFixedSize(480, 480);

    drawBoard();

    mainLayout->addLayout(topBarLayout);
    mainLayout->addWidget(boardView, 0, Qt::AlignCenter); 
    
    //pieces
    //black
    setupPiece(":/resources/pieces/rook-b.svg",   0, 0, PieceColor::Black, PieceType::Rook);
    setupPiece(":/resources/pieces/knight-b.svg", 1, 0, PieceColor::Black, PieceType::Knight);
    setupPiece(":/resources/pieces/bishop-b.svg", 2, 0, PieceColor::Black, PieceType::Bishop);
    setupPiece(":/resources/pieces/queen-b.svg",  3, 0, PieceColor::Black, PieceType::Queen);
    setupPiece(":/resources/pieces/king-b.svg",   4, 0, PieceColor::Black, PieceType::King);
    setupPiece(":/resources/pieces/bishop-b.svg", 5, 0, PieceColor::Black, PieceType::Bishop);
    setupPiece(":/resources/pieces/knight-b.svg", 6, 0, PieceColor::Black, PieceType::Knight);
    setupPiece(":/resources/pieces/rook-b.svg",   7, 0, PieceColor::Black, PieceType::Rook);
    setupPiece(":/resources/pieces/pawn-b.svg",   0, 1, PieceColor::Black, PieceType::Pawn);
    setupPiece(":/resources/pieces/pawn-b.svg",   1, 1, PieceColor::Black, PieceType::Pawn);
    setupPiece(":/resources/pieces/pawn-b.svg",   2, 1, PieceColor::Black, PieceType::Pawn);
    setupPiece(":/resources/pieces/pawn-b.svg",   3, 1, PieceColor::Black, PieceType::Pawn);
    setupPiece(":/resources/pieces/pawn-b.svg",   4, 1, PieceColor::Black, PieceType::Pawn);
    setupPiece(":/resources/pieces/pawn-b.svg",   5, 1, PieceColor::Black, PieceType::Pawn);
    setupPiece(":/resources/pieces/pawn-b.svg",   6, 1, PieceColor::Black, PieceType::Pawn);
    setupPiece(":/resources/pieces/pawn-b.svg",   7, 1, PieceColor::Black, PieceType::Pawn);

    //white
    setupPiece(":/resources/pieces/pawn-w.svg",   0, 6, PieceColor::White, PieceType::Pawn);
    setupPiece(":/resources/pieces/pawn-w.svg",   1, 6, PieceColor::White, PieceType::Pawn);
    setupPiece(":/resources/pieces/pawn-w.svg",   2, 6, PieceColor::White, PieceType::Pawn);
    setupPiece(":/resources/pieces/pawn-w.svg",   3, 6, PieceColor::White, PieceType::Pawn);
    setupPiece(":/resources/pieces/pawn-w.svg",   4, 6, PieceColor::White, PieceType::Pawn);
    setupPiece(":/resources/pieces/pawn-w.svg",   5, 6, PieceColor::White, PieceType::Pawn);
    setupPiece(":/resources/pieces/pawn-w.svg",   6, 6, PieceColor::White, PieceType::Pawn);
    setupPiece(":/resources/pieces/pawn-w.svg",   7, 6, PieceColor::White, PieceType::Pawn);
    setupPiece(":/resources/pieces/rook-w.svg",   0, 7, PieceColor::White, PieceType::Rook);
    setupPiece(":/resources/pieces/knight-w.svg", 1, 7, PieceColor::White, PieceType::Knight);
    setupPiece(":/resources/pieces/bishop-w.svg", 2, 7, PieceColor::White, PieceType::Bishop);
    setupPiece(":/resources/pieces/queen-w.svg",  3, 7, PieceColor::White, PieceType::Queen);
    setupPiece(":/resources/pieces/king-w.svg",   4, 7, PieceColor::White, PieceType::King);
    setupPiece(":/resources/pieces/bishop-w.svg", 5, 7, PieceColor::White, PieceType::Bishop);
    setupPiece(":/resources/pieces/knight-w.svg", 6, 7, PieceColor::White, PieceType::Knight);
    setupPiece(":/resources/pieces/rook-w.svg",   7, 7, PieceColor::White, PieceType::Rook);


    controller = new ChessController(this);


    // connections
    connect(backButton, &QPushButton::clicked, this, &GameScreen::backToMenuRequested);
    connect(controller, &ChessController::engineMoved, this, &GameScreen::onEngineMoved);
}

void GameScreen::drawBoard() {
    const int squareSize = 60;
    
    QColor white(240, 217, 181);
    QColor black(181, 136, 99);

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            
            QGraphicsRectItem *square = new QGraphicsRectItem(col * squareSize, row * squareSize, squareSize, squareSize);
            
            if ((row + col) % 2 == 0) {
                square->setBrush(QBrush(white));
            } else {
                square->setBrush(QBrush(black));
            }
            
            square->setPen(Qt::NoPen);
            boardScene->addItem(square);
        }
    }
}

void GameScreen::setupPiece(const QString& svgPath, int col, int row, PieceColor color, PieceType type) {
    ChessPiece* piece = new ChessPiece(svgPath);
    piece->setScale(0.5); 
    piece->setPos(col * 60, row * 60); 
    
    piece->setPieceColor(color);
    piece->setPieceType(type);
    piece->setGridPosition(col, row);
    
    connect(piece, &ChessPiece::userMoveRequested, this, &GameScreen::onUserMoveRequested);
    
    boardScene->addItem(piece);
    pieceRegistry[col][row] = piece;
}




void GameScreen::onUserMoveRequested(ChessPiece* piece, int fromCol, int fromRow, int toCol, int toRow) {
    
    if ((piece->getPieceColor() == currentTurn && controller->isValidMove(piece, fromCol, fromRow, toCol, toRow)) ) {
        executeMove(fromCol, fromRow, toCol, toRow);
        if (controller->isCheckmate(PieceColor::Black)) { // check for checkmate after the user's move
            gameOver("You win! Checkmate!");
        } else {
            controller->triggerEngineMove();
        }
        
    } else {
        piece->setPos(fromCol * 60, fromRow * 60);
    }
}

void GameScreen::onEngineMoved(int fromCol, int fromRow, int toCol, int toRow, QString promotedTo) {
    executeMove(fromCol, fromRow, toCol, toRow);
    
    // handle pawn promotion if needed
    if (!promotedTo.isEmpty()) {
        
        // delete the pawn that's being promoted
        if (pieceRegistry[toCol][toRow]) {
            boardScene->removeItem(pieceRegistry[toCol][toRow]);
            delete pieceRegistry[toCol][toRow];
            pieceRegistry[toCol][toRow] = nullptr;
        }
        
        QString svgPath;
        PieceType selectedType;
        
        if (promotedTo == "queen") {
            svgPath = ":/resources/pieces/queen-b.svg";
            selectedType = PieceType::Queen;
        } else if (promotedTo == "rook") {
            svgPath = ":/resources/pieces/rook-b.svg";
            selectedType = PieceType::Rook;
        } else if (promotedTo == "bishop") {
            svgPath = ":/resources/pieces/bishop-b.svg";
            selectedType = PieceType::Bishop;
        } else {
            svgPath = ":/resources/pieces/knight-b.svg";
            selectedType = PieceType::Knight;
        }
        
        // setup the new piece on the board
        setupPiece(svgPath, toCol, toRow, PieceColor::Black, selectedType);

    }

    // check for checkmate after the promotion
    if (controller->isCheckmate(PieceColor::White)) {
        gameOver("Checkmate! You lose!");
    }
}

void GameScreen::gameOver(const QString &message) {
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Game over");
    msgBox.setText(message);
    msgBox.addButton("OK", QMessageBox::AcceptRole);
    QPushButton *exitButton = msgBox.addButton("Exit application", QMessageBox::RejectRole);
    msgBox.exec();

    if (msgBox.clickedButton() == exitButton) {
        qApp->quit();
    }
}



void GameScreen::promotePawn(int col, int row, PieceColor color) {
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Pawn promtoion");
    msgBox.setText("Choose a piece to promote your pawn to:");

    QPushButton *queenBtn = msgBox.addButton("Queen", QMessageBox::ActionRole);
    QPushButton *rookBtn = msgBox.addButton("Rook", QMessageBox::ActionRole);
    QPushButton *bishopBtn = msgBox.addButton("Bishop", QMessageBox::ActionRole);
    QPushButton *knightBtn = msgBox.addButton("Knight", QMessageBox::ActionRole);

    msgBox.exec();

    PieceType selectedType;
    QString svgPath;

    // determine which button was clicked and set the selected piece type and corresponding SVG path
    if (msgBox.clickedButton() == queenBtn) {
        selectedType = PieceType::Queen;
        svgPath = (color == PieceColor::White) ? ":/resources/pieces/queen-w.svg" : ":/resources/pieces/queen-b.svg";
    } else if (msgBox.clickedButton() == rookBtn) {
        selectedType = PieceType::Rook;
        svgPath = (color == PieceColor::White) ? ":/resources/pieces/rook-w.svg" : ":/resources/pieces/rook-b.svg";
    } else if (msgBox.clickedButton() == bishopBtn) {
        selectedType = PieceType::Bishop;
        svgPath = (color == PieceColor::White) ? ":/resources/pieces/bishop-w.svg" : ":/resources/pieces/bishop-b.svg";
    } else {
        selectedType = PieceType::Knight;
        svgPath = (color == PieceColor::White) ? ":/resources/pieces/knight-w.svg" : ":/resources/pieces/knight-b.svg";
    }

    // delete the pawn that's being promoted
    if (pieceRegistry[col][row]) {
        boardScene->removeItem(pieceRegistry[col][row]);
        delete pieceRegistry[col][row];
        pieceRegistry[col][row] = nullptr;
    }

    // create the new piece and place it on the board
    setupPiece(svgPath, col, row, color, selectedType); 
    controller->promotePawnToEngine(col, row, color, selectedType); // inform the engine about the promotion
}

void GameScreen::executeMove(int fromCol, int fromRow, int toCol, int toRow) {
    ChessPiece* pieceToMove = pieceRegistry[fromCol][fromRow];
    if (!pieceToMove) return;

    //handle capture
    if (pieceRegistry[toCol][toRow] != nullptr) {
        boardScene->removeItem(pieceRegistry[toCol][toRow]);
        delete pieceRegistry[toCol][toRow];
    }

    //move piece
    pieceToMove->setPos(toCol * 60, toRow * 60);
    pieceToMove->setGridPosition(toCol, toRow);
    
    pieceRegistry[toCol][toRow] = pieceToMove;
    pieceRegistry[fromCol][fromRow] = nullptr;

    // chechk for pawn promotion
    if (pieceToMove->getPieceType() == PieceType::Pawn) {
        if (pieceToMove->getPieceColor() == PieceColor::White && toRow == 0) {
            promotePawn(toCol, toRow, PieceColor::White);
        }/* else if (pieceToMove->getPieceColor() == PieceColor::Black && toRow == 7) {
            promotePawn(toCol, toRow, PieceColor::Black);
        }*/
    }

    currentTurn = (currentTurn == PieceColor::White) ? PieceColor::Black : PieceColor::White;
}
