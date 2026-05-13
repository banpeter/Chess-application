#pragma once

#include <QObject>
#include <QString>
#include <QDebug>
#include "engine/engine.h"
#include "ChessPiece.h"
//#include "engine.h"

class ChessController : public QObject {
    Q_OBJECT
    Board board = Board();

public:
    explicit ChessController(QObject *parent = nullptr);

    bool isValidMove(int fromCol, int fromRow, int toCol, int toRow);

    void triggerEngineMove();
    void promotePawnToEngine(int col, int row, PieceType selectedType);

    
    signals:
    void movePieceCommand(int fromCol, int fromRow, int toCol, int toRow);
    void gameOverCommand(const QString& message);
    
    private:
    // Board engineBoard;
    QString pieceTypeToString(PieceType type);
    QString pieceColorToString(PieceColor color);
};