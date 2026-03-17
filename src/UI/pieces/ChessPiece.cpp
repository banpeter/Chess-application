#include "ChessPiece.h"
#include <cmath>

ChessPiece::ChessPiece(const QString &fileName, QGraphicsItem *parent)
    : QGraphicsSvgItem(fileName, parent) {
    
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setZValue(1); 
}

void ChessPiece::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsSvgItem::mouseReleaseEvent(event);

    qreal currentX = pos().x();
    qreal currentY = pos().y();

    int squareSize = 60;
    qreal gridX = std::floor((currentX + squareSize / 2.0) / squareSize) * squareSize;
    qreal gridY = std::floor((currentY + squareSize / 2.0) / squareSize) * squareSize;

    setPos(gridX, gridY);
}