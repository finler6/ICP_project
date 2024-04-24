#include "Obstacle.h"

Obstacle::Obstacle(std::pair<double, double> position, double size)
    : position(position), size(size) {}

std::pair<double, double> Obstacle::getPosition() const {
    return position;
}

double Obstacle::getSize() const {
    return size;
}
