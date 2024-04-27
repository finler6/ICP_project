#include "Obstacle.h"
#include <iostream>

Obstacle::Obstacle(std::pair<double, double> position, double size)
    : position(position), size(size) {
    std::cout << "Obstacle created at (" << position.first << ", " << position.second << ") with size " << size << std::endl;
}

std::pair<double, double> Obstacle::getPosition() const {
    return position;
}

QRectF Obstacle::getBounds() const {
    // Assuming the size is the diameter of a circle centered at 'position'
    double halfSize = size / 2.0;
    return QRectF(position.first - halfSize, position.second - halfSize, size, size);
}

double Obstacle::getSize() const {
    return size;
}

