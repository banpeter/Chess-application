#pragma once

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsSvgItem>
#include <QMessageBox>
#include <QPushButton>

#include "ChessPiece.h"
#include "ChessController.h"

class GameScreen : public QWidget {
    Q_OBJECT

public:
    explicit GameScreen(QWidget *parent = nullptr);

signals:
    void backToMenuRequested(); 

private slots:
    void handleMoveRequest(ChessPiece* piece, int fromCol, int fromRow, int toCol, int toRow);

private:
    QPushButton *backButton;
    QGraphicsView *boardView;
    QGraphicsScene *boardScene;

    ChessPiece* pieceRegistry[8][8];

    ChessController* controller;

    void drawBoard();
    void setupPiece(const QString& svgPath, int col, int row, PieceColor color, PieceType type);

    void showGameOver(const QString& message);

    void handlePawnPromotion(int toCol, int toRow, PieceColor color);
};