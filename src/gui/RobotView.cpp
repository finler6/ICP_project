
// RobotView.cpp
#include "RobotView.h"

RobotView::RobotView() : orientation(0), size(20) {  // Инициализация размера
    setPosition(QPointF(0, 0));
}

QRectF RobotView::boundingRect() const {
    return QRectF(-size/2, -size/2, size, size);  // Использование размера для определения границ
}

void RobotView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setBrush(Qt::gray);
    painter->drawEllipse(boundingRect());

    painter->setPen(Qt::red);
    painter->drawLine(QPointF(0, 0), QPointF(size/2 * cos(orientation * M_PI / 180), size/2 * sin(orientation * M_PI / 180)));
}

void RobotView::setPosition(const QPointF &pos) {
    position = pos;
    setPos(position);
}

void RobotView::setOrientation(double angle) {
    orientation = angle;
    setRotation(orientation);
}

void RobotView::setSize(double newSize) {
    prepareGeometryChange();
    size = newSize;
    update();
}