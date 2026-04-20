#pragma once

#include <QGraphicsSvgItem>
#include <QGraphicsSceneMouseEvent>
#include <QString>

class ChessPiece : public QGraphicsSvgItem {
    Q_OBJECT

public:
    explicit ChessPiece(const QString &fileName, QGraphicsItem *parent = nullptr);

    void setPieceID(const QString& id) {pieceID = id; }
    QString getPieceID() const { return pieceID; }

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
    QString pieceID;
    int currentCol, currentRow;
};