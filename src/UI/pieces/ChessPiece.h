#pragma once

#include <QGraphicsSvgItem>
#include <QGraphicsSceneMouseEvent>

class ChessPiece : public QGraphicsSvgItem {
public:
    explicit ChessPiece(const QString &fileName, QGraphicsItem *parent = nullptr);

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};