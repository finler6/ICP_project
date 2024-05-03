#ifndef OBSTACLEVIEW_H
#define OBSTACLEVIEW_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QRectF>
#include "code/Obstacle.h"
#include "code/SimulationEngine.h"

class ObstacleView : public QGraphicsItem {
public:
    explicit ObstacleView(SimulationEngine* engine, int id, const QRectF &initialBounds, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void setBounds(const QRectF &newBounds);
    double getSize() const;
    void setSize(double size);
    int getId() const;  
    void setId(int newId);  
    void updateObstacleView();
private:
    QRectF bounds;
    int id;
    SimulationEngine* engine;
};

#endif 

