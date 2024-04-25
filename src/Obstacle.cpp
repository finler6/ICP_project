#include "Obstacle.h"
#include <iostream>

Obstacle::Obstacle(std::pair<double, double> position, double size)
    : position(position), size(size) {
    std::cout << "Obstacle created at (" << position.first << ", " << position.second << ") with size " << size << std::endl;
}
std::pair<double, double> Obstacle::getPosition() const {
    return position;
}

double Obstacle::getSize() const {
    return size;
}
