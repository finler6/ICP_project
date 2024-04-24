#pragma once
#include <utility>  // For std::pair

class Obstacle {
public:
    Obstacle(std::pair<double, double> position, double size);
    
    std::pair<double, double> getPosition() const;
    double getSize() const;

private:
    std::pair<double, double> position;  // Координаты центра препятствия (x, y)
    double size;  // Размер препятствия (может быть интерпретирован как радиус, если препятствие круглое)
};
