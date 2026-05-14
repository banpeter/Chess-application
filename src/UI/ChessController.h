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

    bool isValidMove(ChessPiece* piece, int fromCol, int fromRow, int toCol, int toRow);
    bool isCheckmate(PieceColor color);

    void triggerEngineMove();
    void promotePawnToEngine(int col, int row, PieceColor color, PieceType selectedType);

    
signals:
    void engineMoved(int fromCol, int fromRow, int toCol, int toRow, QString promotedTo = "");
    
private:
    QString pieceTypeToString(PieceType type);
    QString pieceColorToString(PieceColor color);
};