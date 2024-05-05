/**
 * @file AutonomousRobot.cpp
 * @brief Definition of the AutonomousRobot class, which extends the Robot base class with specific functionalities for autonomous navigation and obstacle detection.
 *
 * @author Pavel Stepanov (xstepa77)
 * @author Gleb Litvinchuk (xlitvi02)
 * @date 2024-05-05
 */
#include "ObstacleView.h"

/**
 * @brief Construct a new ObstacleView::ObstacleView object
 *
 * @param engine Simulation engine
 * @param id Obstacle ID
 * @param initialBounds Initial bounds of the obstacle
 * @param parent Parent item
 */
ObstacleView::ObstacleView(SimulationEngine* engine, int id, const QRectF &initialBounds, QGraphicsItem *parent)
    : id(id), bounds(initialBounds), engine(engine) {
    setParentItem(parent);
}

QPointF ObstacleView::getPosition() const {
    return QPointF(bounds.center().x(), bounds.center().y());
}

QRectF ObstacleView::boundingRect() const {
    return bounds;
}

/**
 * @brief Set the position of the obstacle
 *
 * @param position New position
 */
double ObstacleView::getSize() const {
    return bounds.width();
}

/**
 * @brief Set the size of the obstacle
 *
 * @param size New size
 */
int ObstacleView::getId() const {
    return id;
}

/**
 * @brief Get the ID of the obstacle
 *
 * @return int Obstacle ID
 */
void ObstacleView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setBrush(Qt::black);
    painter->drawRect(bounds);
}
