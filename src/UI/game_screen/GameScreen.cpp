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
    backButton = new QPushButton("Vissza a menübe", this);
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
    addPiece(":/resources/pieces/rook-b.svg",   0, 0); // rook
    addPiece(":/resources/pieces/knight-b.svg", 1, 0); // knight
    addPiece(":/resources/pieces/bishop-b.svg", 2, 0); // bishop
    addPiece(":/resources/pieces/queen-b.svg",  3, 0); // queen
    addPiece(":/resources/pieces/king-b.svg",   4, 0); // king
    addPiece(":/resources/pieces/bishop-b.svg", 5, 0); // bishop
    addPiece(":/resources/pieces/knight-b.svg", 6, 0); // knight
    addPiece(":/resources/pieces/rook-b.svg",   7, 0); // rook
    for (int col = 0; col < 8; ++col) {                // pawns
        addPiece(":/resources/pieces/pawn-b.svg", col, 1);
    }

    //white
    for (int col = 0; col < 8; ++col) {                // pawns
        addPiece(":/resources/pieces/pawn-w.svg", col, 6);
    }
    addPiece(":/resources/pieces/rook-w.svg",   0, 7); // rook
    addPiece(":/resources/pieces/knight-w.svg", 1, 7); // knight
    addPiece(":/resources/pieces/bishop-w.svg", 2, 7); // bishop
    addPiece(":/resources/pieces/queen-w.svg",  3, 7); // queen
    addPiece(":/resources/pieces/king-w.svg",   4, 7); // king
    addPiece(":/resources/pieces/bishop-w.svg", 5, 7); // bishop
    addPiece(":/resources/pieces/knight-w.svg", 6, 7); // knight
    addPiece(":/resources/pieces/rook-w.svg",   7, 7); // rook
    
    
    // connections
    connect(backButton, &QPushButton::clicked, this, &GameScreen::backToMenuRequested);
}

void GameScreen::drawBoard() {
    const int squareSize = 60;
    
    QColor lightColor(240, 217, 181);
    QColor darkColor(181, 136, 99);

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            
            QGraphicsRectItem *square = new QGraphicsRectItem(col * squareSize, row * squareSize, squareSize, squareSize);
            
            if ((row + col) % 2 == 0) {
                square->setBrush(QBrush(lightColor));
            } else {
                square->setBrush(QBrush(darkColor));
            }
            
            square->setPen(Qt::NoPen);
            boardScene->addItem(square);
        }
    }
}