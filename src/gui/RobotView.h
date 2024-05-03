// RobotView.h
#ifndef ROBOTVIEW_H
#define ROBOTVIEW_H

#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QPainter>
#include <cmath>
#include "code/Robot.h"
#include "code/SimulationEngine.h"

#pragma once

class RobotView : public QGraphicsItem {
public:
    explicit RobotView(SimulationEngine* engine, int id, QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void setPosition(const QPointF &position);
    void setOrientation(double angle);
    void setSize(double size);  

    void setSensorRange(double range); 
    void setRobot(Robot* robot);
    int getId() const;
    Robot* getRobot() const;
    double getSpeed() const;
    double getOrientation() const;
    double getSensorRange() const;
    void updateRobotView();

signals:
    void requestUpdate(int id);


private:
    SimulationEngine* engine;
    QPointF position;
    double orientation;
    int robotId;
    Robot* robot;
    double size;  
    double sensorRange;  
    int id;

};


#endif // ROBOTVIEW_H