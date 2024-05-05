/**
 * @file AutonomousRobot.cpp
 * @brief Definition of the AutonomousRobot class, which extends the Robot base class with specific functionalities for autonomous navigation and obstacle detection.
 *
 * @author Pavel Stepanov (xstepa77)
 * @author Gleb Litvinchuk (xlitvi02)
 * @date 2024-05-05
 */
#ifndef OBSTACLEVIEW_H
#define OBSTACLEVIEW_H

#include "QGraphicsRectItem"
#include "QObject"
#include "QGraphicsItem"
#include "QPainter"
#include "QRectF"
#include "QPointF"
#include "code/Obstacle.h"
#include "code/SimulationEngine.h"

/**
 * @brief The ObstacleView class represents a graphical view of an obstacle in the simulation.
 */
class ObstacleView : public QGraphicsItem {
public:
    explicit ObstacleView(SimulationEngine* engine, int id, const QRectF &initialBounds, QGraphicsItem *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    [[nodiscard]]int getId() const;
    [[nodiscard]] double getSize() const;
    [[nodiscard]] QPointF getPosition() const;
    [[nodiscard]] QRectF boundingRect() const override;

private:
    int id;
    QRectF bounds;
    SimulationEngine* engine;

};

#endif 

