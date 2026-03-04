#include "GameScreen.h"
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