// ObstacleView.cpp
#include "ObstacleView.h"

ObstacleView::ObstacleView(const QRectF &initialBounds) : bounds(initialBounds) {
}

QRectF ObstacleView::boundingRect() const {
    return bounds;
}

void ObstacleView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setBrush(Qt::black);
    painter->drawRect(bounds);
}

void ObstacleView::setBounds(const QRectF &newBounds) {
    prepareGeometryChange();  // Notify QGraphicsScene of geometry change
    bounds = newBounds;
    update();  // Request a redraw
}