
// RobotView.cpp
#include "RobotView.h"

RobotView::RobotView() : orientation(0), size(20), sensorRange(100) {  // Инициализация по умолчанию
    setPosition(QPointF(0, 0));
}

void RobotView::setSensorRange(double range) {
    sensorRange = range;
    update();
}

QRectF RobotView::boundingRect() const {
    return QRectF(-size/2, -size/2, size, size);  // Использование размера для определения границ
}

void RobotView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setBrush(Qt::gray);
    painter->drawEllipse(boundingRect());

    // Отрисовка направления робота
    painter->setPen(Qt::red);
    painter->drawLine(QPointF(0, 0), QPointF(size/2 * cos(orientation * M_PI / 180), size/2 * sin(orientation * M_PI / 180)));

    // Отрисовка сенсорного поля
    QPainterPath path;
    path.moveTo(0, 0);
    double startAngle = orientation - 30;  // начальный угол сенсора относительно текущего направления
    double sweepLength = 60;  // угол охвата сенсора

    // Преобразование углов в формат, используемый QPainter (против часовой стрелки, начиная с 3 часов)
    startAngle = -startAngle - sweepLength;
    QRectF rectangle(-sensorRange, -sensorRange, 2 * sensorRange, 2 * sensorRange);
    path.arcTo(rectangle, startAngle, sweepLength);

    path.closeSubpath();
    painter->setBrush(QColor(255, 255, 0, 100));  // Желтый цвет с прозрачностью для визуализации сенсорного поля
    painter->drawPath(path);
}

void RobotView::setPosition(const QPointF &pos) {
    position = pos;
    setPos(position);
}

void RobotView::setOrientation(double angle) {
    orientation = angle;  // Обновление угла ориентации
    update();             // Перерисовка объекта с новыми данными
}

void RobotView::setSize(double newSize) {
    prepareGeometryChange();
    size = newSize;
    update();
}