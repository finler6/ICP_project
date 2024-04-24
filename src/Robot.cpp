#include "Robot.h"
#include <cmath> // For trigonometric functions

Robot::Robot(int id, std::pair<double, double> position, double velocity, double orientation, double size)
    : id(id), position(position), velocity(velocity), orientation(orientation), size(size) {}

std::pair<double, double> Robot::getPosition() const {
    return position;
}

double Robot::getSize() const {
    return size;
}

double Robot::getOrientation() const {
    return orientation;
}
