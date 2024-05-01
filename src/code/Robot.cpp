#include "Robot.h"
#include <cmath> // For trigonometric functions
#include <iostream>

Robot::Robot(int id, std::pair<double, double> position, double velocity, double orientation, double sensorRange)
    : id(id), position(position), velocity(velocity), orientation(orientation), sensorRange(sensorRange) {}

std::pair<double, double> Robot::getPosition() const {
    return position;
}


double Robot::getRange() const {
    return sensorRange;
}

double Robot::getOrientation() const {
    return orientation;
}

bool Robot::isTaskCompleted() const {
    //std::cout << "Robot " << id << " task completed: " << taskCompleted << std::endl;
    return taskCompleted;
}
