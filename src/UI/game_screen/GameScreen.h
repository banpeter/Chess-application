#pragma once

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsSvgItem>

#include "ChessPiece.h"

class GameScreen : public QWidget {
    Q_OBJECT

public:
    explicit GameScreen(QWidget *parent = nullptr);

signals:
    void backToMenuRequested(); 

private:
    QPushButton *backButton;
    QGraphicsView *boardView;
    QGraphicsScene *boardScene;

    ChessPiece *whiteKnight;

    void drawBoard();
};