#include "AutonomousRobot.h"
#include <cmath>
#include <iostream>

AutonomousRobot::AutonomousRobot(int id, std::pair<double, double> position, double velocity, double orientation, double size)
    : Robot(id, position, velocity, orientation, size), avoidanceAngle(30.0) {}  // Задаем угол уклонения 30 градусов

void AutonomousRobot::move(double maxWidth, double maxHeight) {
    // Двигаемся вперед с текущей скоростью и ориентацией
    std::cout << "Current Speed (Autonomous): " << velocity << std::endl;

    double newX = position.first + velocity * cos(orientation * M_PI / 180.0);
    double newY = position.second + velocity * sin(orientation * M_PI / 180.0);

    // Проверка на достижение границ
    bool atEdge = false;
    if (newX < 0 || newX > maxWidth || newY < 0 || newY > maxHeight) {
        atEdge = true;
        newX = std::max(0.0, std::min(newX, maxWidth)); // Ограничиваем движение внутри рамок
        newY = std::max(0.0, std::min(newY, maxHeight));
    }

    position.first = newX;
    position.second = newY;

    // Если робот достиг края, обрабатываем это как столкновение
    if (atEdge) {
        handleCollision();
    }
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
