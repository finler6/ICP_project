
// RobotView.cpp
#include "RobotView.h"

RobotView::RobotView(SimulationEngine* engine, int id, QGraphicsItem *parent)
    : QGraphicsItem(parent), orientation(0), size(20), sensorRange(100), engine(engine), id(id) {
    setPosition(QPointF(0, 0));
}
void RobotView::setSensorRange(double range) {
    sensorRange = range;
    update();
}

QRectF RobotView::boundingRect() const {
    return QRectF(-size/2, -size/2, size, size);  
}

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



void RobotView::setPosition(const QPointF &pos) {
    position = pos;
    setPos(position);
}

void RobotView::setOrientation(double angle) {
    orientation = angle;  
    update();             
}

void RobotView::setSize(double newSize) {
    prepareGeometryChange();
    size = newSize;
    update();   
}                       

void RobotView::setRobot(Robot* robot) {
    if (robot) {
        this->robot = robot;
        this->robotId = robot->getID();
    } else {
        qDebug() << "Null robot pointer passed to RobotView::setRobot.";
        this->robot = nullptr;  // Явно устанавливаем nullptr для избежания неопределённого поведения
    }
}


    int RobotView::getId() const {
        qDebug() << "RobotView returning ID:" << id;
        return id;
    }

    double RobotView::getSpeed() const {
        return robot->getSpeed();
    }

    double RobotView::getOrientation() const {
        return robot->getOrientation();
    }

double RobotView::getSensorRange() const {
    return robot->getRange();
}

    Robot* RobotView::getRobot() const {
        return robot;
    }

QPointF RobotView::getPosition() const {
    return position;
}