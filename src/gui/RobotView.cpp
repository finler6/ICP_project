/**
 * @file AutonomousRobot.cpp
 * @brief Definition of the AutonomousRobot class, which extends the Robot base class with specific functionalities for autonomous navigation and obstacle detection.
 *
 * @author Pavel Stepanov (xstepa77)
 * @author Gleb Litvinchuk (xlitvi02)
 * @date 2024-05-05
 */
#include "RobotView.h"

/**
 * @brief Construct a new RobotView object
 *
 * @param engine
 * @param id
 * @param parent
 */
RobotView::RobotView(SimulationEngine* engine, int id, QGraphicsItem *parent)
    : QGraphicsItem(parent), id(id), engine(engine), size(20), orientation(0), sensorRange(100)  {
    setPosition(QPointF(0, 0));
}

/**
 * @brief Get the ID of the robot
 *
 * @return int
 */
int RobotView::getId() const {
    return id;
}

/**
 * @brief Get the speed of the robot
 *
 * @return double
 */
double RobotView::getSpeed() const {
    return robot->getSpeed();
}

/**
 * @brief Get the orientation of the robot
 *
 * @return double
 */
double RobotView::getOrientation() const {
    return robot->getOrientation();
}

/**
 * @brief Get the sensor range of the robot
 *
 * @return double
 */
double RobotView::getSensorRange() const {
    return robot->getRange();
}

/**
 * @brief Get the position of the robot
 *
 * @return QPointF
 */
QPointF RobotView::getPosition() const {
    return position;
}

/**
 * @brief set sensor range
 */
void RobotView::setSensorRange(double range) {
    sensorRange = range;
    update();
}

/**
 * @brief Set the position of the robot
 *
 * @param pos
 */
void RobotView::setPosition(const QPointF &pos) {
    position = pos;
    setPos(position);
}

/**
 * @brief Set the orientation of the robot
 *
 * @param angle
 */
void RobotView::setOrientation(double angle) {
    orientation = angle;
    update();
}

void RobotView::setRobot(Robot* robot) {
    if (robot) {
        this->robot = robot;
        this->robotId = robot->getID();
    } else {
        this->robot = nullptr;
    }
}


QRectF RobotView::boundingRect() const {
    return QRectF(-size/2, -size/2, size, size);  
}

/**
 * @brief Paint the robot
 *
 * @param painter
 * @param option
 * @param widget
 */
void RobotView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setBrush(Qt::gray);
    painter->drawEllipse(boundingRect());

    painter->setPen(Qt::red);
    painter->drawLine(QPointF(0, 0), QPointF(size/2 * cos(orientation * M_PI / 180), size/2 * sin(orientation * M_PI / 180)));

    QPainterPath path;
    path.moveTo(0, 0);
    double startAngle = orientation - 30;  
    double sweepLength = 60;  


    startAngle = -startAngle - sweepLength;
    QRectF rectangle(-(sensorRange + 10), -(sensorRange + 10), 2 * (sensorRange + 10), 2 * (sensorRange + 10));
    path.arcTo(rectangle, startAngle, sweepLength);

    path.closeSubpath();
    painter->setBrush(QColor(255, 255, 0, 100));  
    painter->drawPath(path);
}
