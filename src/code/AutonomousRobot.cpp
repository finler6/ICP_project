#include "AutonomousRobot.h"
#include <QDebug>
#include <cmath>
#include <iostream>
#include <QRectF>

struct SensorArea {
    double centerX;
    double centerY;
    double radius;
    double angleStart;
    double angleEnd;
};

AutonomousRobot::AutonomousRobot(int id, std::pair<double, double> position, double velocity, double orientation, double sensorRange, double maxWidth, double maxHeight, Environment* env)
    : Robot(id, position, velocity, orientation, sensorRange), avoidanceAngle(orientation), maxWidth_(maxWidth), maxHeight_(maxHeight), environment(env), radius(10.0) {
    if (!environment) {
        std::cerr << "Environment pointer is null" << std::endl;
    }
    this->sensorRange = sensorRange; 
}


bool AutonomousRobot::detectObstacle(double maxWidth, double maxHeight) {
    double radianOrientation = getOrientation() * M_PI / 180.0;
    double robotRadius = 10.0; 

    for (int angle = -30; angle <= 30; angle += 2) { 
        double currentAngle = radianOrientation + angle * M_PI / 180.0;
        double projectedX = position.first + (sensorRange + robotRadius) * cos(currentAngle);
        double projectedY = position.second + (sensorRange + robotRadius) * sin(currentAngle);
        for (const auto& obstacle : environment->getObstacles()) {
            QRectF bounds = obstacle->getBounds().adjusted(-robotRadius, -robotRadius, robotRadius, robotRadius);
            if (lineIntersectsRect(position.first, position.second, projectedX, projectedY, bounds)) {
                qDebug() << "Robot ID:" << id << " detected an obstacle using sensor at angle: " << angle;
                return true;
            }
        }
        for (const auto& otherRobot : environment->getRobots()) {
            if (otherRobot->getID() != this->id) { 
                QRectF otherRobotBounds(
                    otherRobot->getPosition().first - robotRadius,
                    otherRobot->getPosition().second - robotRadius,
                    robotRadius * 2, robotRadius * 2);
                if (lineIntersectsRect(position.first, position.second, projectedX, projectedY, otherRobotBounds)) {
                    qDebug() << "Robot ID:" << id << " detected another robot as obstacle using sensor at angle: " << angle;
                    return true;
                }
            }
        }
    }
    return isEdgeWithinSensorRange(maxWidth, maxHeight);
}





bool AutonomousRobot::isEdgeWithinSensorRange(double maxWidth, double maxHeight) {
    double x = position.first;
    double y = position.second;
    double orientationRad = getOrientation() * M_PI / 180.0;
    double sensorAngle = 15.0 * M_PI / 180.0; 
    double centerX = x + sensorRange * cos(orientationRad);
    double centerY = y + sensorRange * sin(orientationRad);
    double leftX = x + sensorRange * cos(orientationRad - sensorAngle);
    double leftY = y + sensorRange * sin(orientationRad - sensorAngle);
    double rightX = x + sensorRange * cos(orientationRad + sensorAngle);
    double rightY = y + sensorRange * sin(orientationRad + sensorAngle);
    return checkBoundary(leftX, leftY, maxWidth, maxHeight) ||
           checkBoundary(centerX, centerY, maxWidth, maxHeight) ||
           checkBoundary(rightX, rightY, maxWidth, maxHeight);
}

bool AutonomousRobot::checkBoundary(double x, double y, double maxWidth, double maxHeight) {
    return x <= 0 || x >= maxWidth || y <= 0 || y >= maxHeight;
}

void AutonomousRobot::move(double maxWidth, double maxHeight) {
    if (detectObstacle(maxWidth, maxHeight)) {
        handleCollision();  
        qDebug() << "Collision detected, handling collision";
        tryMove(maxWidth, maxHeight);  
    } else {
        qDebug() << "No collision, moving normally";
        double newX = position.first + velocity * cos(orientation * M_PI / 180.0);
        double newY = position.second + velocity * sin(orientation * M_PI / 180.0);
            updatePosition(newX, newY, maxWidth, maxHeight);
    }
}




void AutonomousRobot::updatePosition(double newX, double newY, double maxWidth, double maxHeight) {
    position.first = std::max(0.0, std::min(newX, maxWidth)); 
    position.second = std::max(0.0, std::min(newY, maxHeight));
}


void AutonomousRobot::rotate(double angle) {
    orientation += angle;
    orientation = fmod(orientation, 360.0);  
    qDebug() << "Robot ID:" << id << "rotated by angle:" << angle << "to orientation:" << orientation;
}

void AutonomousRobot::handleCollision() {
    rotate(avoidanceAngle);  
}

void AutonomousRobot::tryMove(double maxWidth, double maxHeight) {
    double radianOrientation = orientation * M_PI / 180.0;
    double newX = position.first + velocity * cos(radianOrientation);
    double newY = position.second + velocity * sin(radianOrientation);

    bool canMoveX = canMoveTo(newX, position.second, maxWidth, maxHeight);
    bool canMoveY = canMoveTo(position.first, newY, maxWidth, maxHeight);

    if (canMoveX && canMoveY) {
        updatePosition(newX, newY, maxWidth, maxHeight);
    } else if (canMoveX) {
        updatePosition(newX, position.second, maxWidth, maxHeight);
    } else if (canMoveY) {
        updatePosition(position.first, newY, maxWidth, maxHeight);
    } else {
        qDebug() << "Robot ID:" << id << " is blocked and cannot move.";
    }
}


bool AutonomousRobot::canMoveTo(double x, double y, double maxWidth, double maxHeight) {
    if (x < 0 || x > maxWidth || y < 0 || y > maxHeight) {
        return false;
    }
    qDebug() << "Trying to move to: (" << x << ", " << y << ")";
    if (isObstacleAt(x, y)) {
        qDebug() << "Obstacle detected at new position!";
        return false; 
    }
    for (const auto& otherRobot : environment->getRobots()) {
        if (otherRobot->getID() != this->id) {
            QRectF otherRobotBounds(
                otherRobot->getPosition().first - 20,
                otherRobot->getPosition().second - 20,
                40, 40); 
            if (otherRobotBounds.contains(x, y)) {
                qDebug() << "Collision with another robot at new position!";
                return false;
            }
        }
    }
    return true;
}



bool AutonomousRobot::isObstacleAt(double x, double y) {
    double robotRadius = 10.0; 
    for (const auto& obstacle : environment->getObstacles()) {
        QRectF bounds = obstacle->getBounds().adjusted(-robotRadius, -robotRadius, robotRadius, robotRadius);
        if (bounds.contains(x, y)) {
            return true; 
        }
    }
    return false;
}



bool AutonomousRobot::lineIntersectsRect(double x1, double y1, double x2, double y2, const QRectF& rect) {
    double left = rect.left();
    double right = rect.right();
    double top = rect.top();
    double bottom = rect.bottom();

    return (lineIntersectsLine(x1, y1, x2, y2, left, top, right, top) ||
            lineIntersectsLine(x1, y1, x2, y2, left, bottom, right, bottom) ||
            lineIntersectsLine(x1, y1, x2, y2, left, top, left, bottom) ||
            lineIntersectsLine(x1, y1, x2, y2, right, top, right, bottom));
}

bool AutonomousRobot::lineIntersectsLine(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
    double denominator = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);

    if (fabs(denominator) < 1e-6) {

        if ((y4 - y3) == 0) { 
            if (y1 != y3) return false; 
            return std::max(x1, x2) >= std::min(x3, x4) && std::min(x1, x2) <= std::max(x3, x4);
        } else if ((x4 - x3) == 0) { 
            if (x1 != x3) return false; 
            return std::max(y1, y2) >= std::min(y3, y4) && std::min(y1, y2) <= std::max(y3, y4);
        }
        return false;
    }

    double ua = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / denominator;
    double ub = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / denominator;

    return ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1;
}





