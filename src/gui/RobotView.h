/**
 * @file AutonomousRobot.cpp
 * @brief Definition of the AutonomousRobot class, which extends the Robot base class with specific functionalities for autonomous navigation and obstacle detection.
 *
 * @author Pavel Stepanov (xstepa77)
 * @author Gleb Litvinchuk (xlitvi02)
 * @date 2024-05-05
 */
 #ifndef ROBOTVIEW_H
#define ROBOTVIEW_H

#include "code/Robot.h"
#include "code/SimulationEngine.h"
#include "QDebug"
#include "QPointF"
#include "QPainter"
#include "QGraphicsItem"
#include "QGraphicsEllipseItem"
#include "cmath"

#pragma once

/**
 * @brief Class representing a graphical representation of a robot in the simulation.
 */
class RobotView : public QGraphicsItem {
public:
    explicit RobotView(SimulationEngine* engine, int id, QGraphicsItem *parent = nullptr);

    [[nodiscard]] QPointF getPosition() const;
    [[nodiscard]] QRectF boundingRect() const override;

    [[nodiscard]] int getId() const;

    [[nodiscard]] double getSpeed() const;
    [[nodiscard]] double getOrientation() const;
    [[nodiscard]] double getSensorRange() const;

    void setRobot(Robot* robot);
    void setOrientation(double angle);
    void setSensorRange(double range);
    void setPosition(const QPointF &position);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    int id;
    int robotId;

    Robot* robot;
    QPointF position;
    SimulationEngine* engine;

    double size;
    double orientation;
    double sensorRange;

};

#endif // ROBOTVIEW_H
