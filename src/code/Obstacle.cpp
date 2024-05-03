#include "Obstacle.h"
#include <iostream>

Obstacle::Obstacle(int id, std::pair<double, double> position, double size)
    : id(id), position(position), size(size) {
    std::cout << "Obstacle created at (" << id << ", " << position.first << ", " << position.second << ") with size " << size << std::endl;
}

std::pair<double, double> Obstacle::getPosition() const {
    return position;
}

QRectF Obstacle::getBounds() const {

    double halfSize = size / 2.0;
    return QRectF(position.first - halfSize, position.second - halfSize, size, size);
}

double Obstacle::getSize() const {
    return size;
}

int Obstacle::getId() const {
    return id;
}


