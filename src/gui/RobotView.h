// RobotView.h
#ifndef ROBOTVIEW_H
#define ROBOTVIEW_H

#include <QGraphicsItem>
#include <QPainter>
#include <cmath>

class RobotView : public QGraphicsItem {
public:
    RobotView();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void setPosition(const QPointF &position);
    void setOrientation(double angle);
    void setSize(double size);  // Добавление метода для изменения размера

    void setSensorRange(double range);  // Метод для установки диапазона сенсора

private:
    QPointF position;
    double orientation;
    double size;  // Добавление атрибута размера

    double sensorRange;  // Добавление атрибута диапазона сенсора
};


#endif // ROBOTVIEW_H