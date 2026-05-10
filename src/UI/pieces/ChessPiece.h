#pragma once

#include <QGraphicsSvgItem>
#include <QGraphicsSceneMouseEvent>
#include <QString>

enum class PieceType {
    Pawn,
    Rook,
    Knight,
    Bishop,
    Queen,
    King
};

enum class PieceColor {
    White,
    Black
};

class ChessPiece : public QGraphicsSvgItem {
    Q_OBJECT

public:
    explicit ChessPiece(const QString &fileName, QGraphicsItem *parent = nullptr);


    void setPieceType(PieceType type) { pieceType = type; }
    PieceType getPieceType() const { return pieceType; }

    void setPieceColor(PieceColor color) { pieceColor = color; }
    PieceColor getPieceColor() const { return pieceColor; }

    void setGridPosition(int col, int row) { 
        currentCol = col; 
        currentRow = row; 
    }
    int getCol() const { return currentCol; }
    int getRow() const { return currentRow; }

signals:
    void moveRequested(ChessPiece* piece, int fromCol, int fromRow, int toCol, int toRow);

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    PieceType pieceType;
    PieceColor pieceColor;
    int currentCol, currentRow;
};