#include "Robot.h"
#include <cmath> 
#include <iostream>
#include <QRectF>


Robot::Robot(int id, std::pair<double, double> position, double velocity, double orientation, double sensorRange)
    : id(id), position(position), velocity(velocity), orientation(orientation), sensorRange(sensorRange) {}

std::pair<double, double> Robot::getPosition() const {
    return position;
}

void Robot::setPosition(const std::pair<double, double>& position) {
    this->position = position;
}

double Robot::getSpeed() const {
    return velocity;
}
double Robot::getRange() const {
    return sensorRange;
}

double Robot::getOrientation() const {
    return orientation;
}

bool Robot::isTaskCompleted() const {
    return taskCompleted;
}

void Robot::setSpeed(double speed) {
    this->velocity = speed;
}

void Robot::setOrientation(double orientation) {
    this->orientation = orientation;
}

void Robot::setSensorSize(double sensorSize) {
    this->sensorRange = sensorSize;
}
