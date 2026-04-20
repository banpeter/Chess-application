#pragma once

#include <QObject>
#include <QString>
#include <QDebug>

class ChessController : public QObject {
    Q_OBJECT

public:
    explicit ChessController(QObject *parent = nullptr);

    bool isValidMove(const QString& pieceId, int fromCol, int fromRow, int toCol, int toRow);

signals:
    void movePieceCommand(int fromCol, int fromRow, int toCol, int toRow);
    void removePieceCommand(const QString& square);

private:
    // Core::Game* backendGame;
};