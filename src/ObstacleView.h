// ObstacleView.h
#ifndef OBSTACLEVIEW_H
#define OBSTACLEVIEW_H

#include <QGraphicsItem>
#include <QPainter>

class ObstacleView : public QGraphicsItem {
public:
    explicit ObstacleView(const QRectF &initialBounds);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void setBounds(const QRectF &newBounds);

private:
    QRectF bounds;
};

#endif // OBSTACLEVIEW_H

