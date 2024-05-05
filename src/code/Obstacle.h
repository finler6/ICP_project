#ifndef OBSTACLE_H
#define OBSTACLE_H
#pragma once
#include <QRectF>
#include <utility>

class Obstacle {
public:
    Obstacle(int id, std::pair<double, double> position, double size);
    std::pair<double, double> getPosition() const;
    double getSize() const;
    QRectF getBounds() const;
    int getId() const;
    void setSize(double newSize) { size = newSize; }
    void setPosition(const std::pair<double, double>& position);

private:
    int id;
    std::pair<double, double> position;
    double size; 
};

#endif // OBSTACLE_H

