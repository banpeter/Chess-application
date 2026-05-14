#pragma once

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsSvgItem>
#include <QMessageBox>

#include "ChessPiece.h"
#include "ChessController.h"

class GameScreen : public QWidget {
    Q_OBJECT

public:
    explicit GameScreen(QWidget *parent = nullptr);

signals:
    void backToMenuRequested(); 

public slots:
    void onEngineMoved(int fromCol, int fromRow, int toCol, int toRow, QString promotedTo);

private slots:
    void onUserMoveRequested(ChessPiece* piece, int fromCol, int fromRow, int toCol, int toRow);

private:
    QPushButton *backButton;
    QGraphicsView *boardView;
    QGraphicsScene *boardScene;

    ChessPiece* pieceRegistry[8][8] = {nullptr};

    PieceColor currentTurn = PieceColor::White;

    ChessController* controller;

    void drawBoard();
    void setupPiece(const QString& svgPath, int col, int row, PieceColor color, PieceType type);

    void promotePawn(int toCol, int toRow, PieceColor color);
    void executeMove(int fromCol, int fromRow, int toCol, int toRow);
    void gameOver(const QString& message);
};