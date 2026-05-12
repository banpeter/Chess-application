#pragma once

#include <QObject>
#include <QString>
#include <QDebug>
#include <QTimer>

#include "ChessPiece.h"
//#include "engine.h"

class ChessController : public QObject {
    Q_OBJECT

public:
    explicit ChessController(QObject *parent = nullptr);

    bool isValidMove(int fromCol, int fromRow, int toCol, int toRow);

    void triggerEngineMove();

signals:
    void movePieceCommand(int fromCol, int fromRow, int toCol, int toRow);
    void gameOverCommand(const QString& message);

private:
    // Board engineBoard;
};