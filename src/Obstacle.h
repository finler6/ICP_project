#ifndef OBSTACLE_H
#define OBSTACLE_H
#pragma once
#include <QRectF>
#include <utility>

class Obstacle {
public:
    Obstacle(std::pair<double, double> position, double size);
    std::pair<double, double> getPosition() const;
    double getSize() const;
    QRectF getBounds() const;

private:
    std::pair<double, double> position;
    double size; // Assuming size is the diameter or edge length if the shape is square
};

#endif // OBSTACLE_H

