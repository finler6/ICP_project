#include "AutonomousRobot.h"
#include <cmath>

AutonomousRobot::AutonomousRobot(int id, std::pair<double, double> position, double velocity, double orientation, double size)
    : Robot(id, position, velocity, orientation, size), avoidanceAngle(30.0) {}  // Задаем угол уклонения 30 градусов

void AutonomousRobot::move() {
    // Двигаемся вперед с текущей скоростью и ориентацией
    position.first += velocity * cos(orientation * M_PI / 180.0);
    position.second += velocity * sin(orientation * M_PI / 180.0);
}

void AutonomousRobot::rotate(double angle) {
    // Поворачиваем на заданный угол
    orientation += angle;
    orientation = fmod(orientation, 360.0);  // Удерживаем угол в пределах 0-360 градусов
}

void AutonomousRobot::handleCollision() {
    // При столкновении поворачиваем на avoidanceAngle градусов для избежания препятствия
    rotate(avoidanceAngle);
}
