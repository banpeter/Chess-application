#include "ChessPiece.h"
#include <cmath>

ChessPiece::ChessPiece(const QString &fileName, QGraphicsItem *parent)
    : QGraphicsSvgItem(fileName, parent) {
    
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setZValue(1); 
}

void ChessPiece::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsSvgItem::mouseReleaseEvent(event);

    int toCol = std::floor((pos().x() + 30) / 60.0);
    int toRow = std::floor((pos().y() + 30) / 60.0);

    if (toCol < 0 || toCol > 7 || toRow < 0 || toRow > 7) {
        setPos(currentCol * 60, currentRow * 60);
        return;
    }

    emit userMoveRequested(this, currentCol, currentRow, toCol, toRow);
}