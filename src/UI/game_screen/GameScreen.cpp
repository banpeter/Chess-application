#include "GameScreen.h"
#include "ChessPiece.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QColor>

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
    boardView->setFixedSize(500, 500);

    drawBoard();

    mainLayout->addLayout(topBarLayout);
    mainLayout->addWidget(boardView, 0, Qt::AlignCenter); 
    
    //pieces
    auto addPiece = [this](const QString& svgPath, int col, int row) {
        ChessPiece* piece = new ChessPiece(svgPath);
        piece->setScale(0.5);
        piece->setPos(col * 60, row * 60);
        boardScene->addItem(piece);
    };

    //black
    setupPiece(":/resources/pieces/rook-b.svg",   0, 0, "rook-b-1");   // rook
    setupPiece(":/resources/pieces/knight-b.svg", 1, 0, "knight-b-1"); // knight
    setupPiece(":/resources/pieces/bishop-b.svg", 2, 0, "bishop-b-1"); // bishop
    setupPiece(":/resources/pieces/queen-b.svg",  3, 0, "queen-b-1");  // queen
    setupPiece(":/resources/pieces/king-b.svg",   4, 0, "king-b-1");   // king
    setupPiece(":/resources/pieces/bishop-b.svg", 5, 0, "bishop-b-2"); // bishop
    setupPiece(":/resources/pieces/knight-b.svg", 6, 0, "knight-b-2"); // knight
    setupPiece(":/resources/pieces/rook-b.svg",   7, 0, "rook-b-2");   // rook
    setupPiece(":/resources/pieces/pawn-b.svg", 0, 1, "pawn-b-1"); // pawn
    setupPiece(":/resources/pieces/pawn-b.svg", 1, 1, "pawn-b-2"); // pawn
    setupPiece(":/resources/pieces/pawn-b.svg", 2, 1, "pawn-b-3"); // pawn
    setupPiece(":/resources/pieces/pawn-b.svg", 3, 1, "pawn-b-4"); // pawn
    setupPiece(":/resources/pieces/pawn-b.svg", 4, 1, "pawn-b-5"); // pawn
    setupPiece(":/resources/pieces/pawn-b.svg", 5, 1, "pawn-b-6"); // pawn
    setupPiece(":/resources/pieces/pawn-b.svg", 6, 1, "pawn-b-7"); // pawn
    setupPiece(":/resources/pieces/pawn-b.svg", 7, 1, "pawn-b-8"); // pawn

    //white
    setupPiece(":/resources/pieces/pawn-w.svg", 0, 6, "pawn-w-1"); // pawn
    setupPiece(":/resources/pieces/pawn-w.svg", 1, 6, "pawn-w-2"); // pawn
    setupPiece(":/resources/pieces/pawn-w.svg", 2, 6, "pawn-w-3"); // pawn
    setupPiece(":/resources/pieces/pawn-w.svg", 3, 6, "pawn-w-4"); // pawn
    setupPiece(":/resources/pieces/pawn-w.svg", 4, 6, "pawn-w-5"); // pawn
    setupPiece(":/resources/pieces/pawn-w.svg", 5, 6, "pawn-w-6"); // pawn
    setupPiece(":/resources/pieces/pawn-w.svg", 6, 6, "pawn-w-7"); // pawn
    setupPiece(":/resources/pieces/pawn-w.svg", 7, 6, "pawn-w-8"); // pawn
    setupPiece(":/resources/pieces/rook-w.svg",   0, 7, "rook-w-1");   // rook
    setupPiece(":/resources/pieces/knight-w.svg", 1, 7, "knight-w-1"); // knight
    setupPiece(":/resources/pieces/bishop-w.svg", 2, 7, "bishop-w-1"); // bishop
    setupPiece(":/resources/pieces/queen-w.svg",  3, 7, "queen-w-1");  // queen
    setupPiece(":/resources/pieces/king-w.svg",   4, 7, "king-w-1");   // king
    setupPiece(":/resources/pieces/bishop-w.svg", 5, 7, "bishop-w-2"); // bishop
    setupPiece(":/resources/pieces/knight-w.svg", 6, 7, "knight-w-2"); // knight
    setupPiece(":/resources/pieces/rook-w.svg",   7, 7, "rook-w-2");   // rook


    controller = new ChessController(this);


    // connections
    connect(backButton, &QPushButton::clicked, this, &GameScreen::backToMenuRequested);
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

void GameScreen::setupPiece(const QString& svgPath, int col, int row, const QString& pieceID) {
    ChessPiece* piece = new ChessPiece(svgPath);
    piece->setScale(0.5); 
    piece->setPos(col * 60, row * 60); 

    piece->setPieceID(pieceID);
    piece->setGridPosition(col, row);

    connect(piece, &ChessPiece::moveRequested, this, &GameScreen::handleMoveRequest);
    
    boardScene->addItem(piece);
    pieceRegistry[col][row] = piece;
}

void GameScreen::handleMoveRequest(ChessPiece* piece, int fromCol, int fromRow, int toCol, int toRow) {

    bool isValid = controller->isValidMove(piece->getPieceID(), fromCol, fromRow, toCol, toRow);

    if (isValid) {
        piece->setPos(toCol * 60, toRow * 60);
        
        piece->setGridPosition(toCol, toRow);

        pieceRegistry[toCol][toRow] = piece;
        pieceRegistry[fromCol][fromRow] = nullptr;

    } else {
        piece->setPos(fromCol * 60, fromRow * 60);
    }
}