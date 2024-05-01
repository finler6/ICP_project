#include "AutonomousRobot.h"
#include <cmath>
#include <iostream>

struct SensorArea {
    double centerX;
    double centerY;
    double radius;
    double angleStart;
    double angleEnd;
};

AutonomousRobot::AutonomousRobot(int id, std::pair<double, double> position, double velocity, double orientation, double sensorRange, Environment* env)
    : Robot(id, position, velocity, 0, sensorRange), avoidanceAngle(orientation), environment(env) {
    if(!environment) {
        std::cerr << "Environment pointer is null" << std::endl;
    }
}  // Задаем угол уклонения 30 градусов

bool AutonomousRobot::detectObstacle() {
    double radianOrientation = getOrientation() * M_PI / 180.0;  // Преобразование угла ориентации в радианы
    double closestObstacleDistance = std::numeric_limits<double>::max();
    bool obstacleDetected = false;
    double sensorAngle = 40.0 * M_PI / 180.0; // Угловой диапазон сенсора в радианах

    for (const auto& obstacle : environment->getObstacles()) {
        double dx = obstacle.getPosition().first - position.first;
        double dy = obstacle.getPosition().second - position.second;
        double distance = sqrt(dx * dx + dy * dy) - obstacle.getSize();

        if (distance < closestObstacleDistance && distance <= sensorRange) {
            double angleToObstacle = atan2(dy, dx);
            double angleDifference = angleToObstacle - radianOrientation;

            angleDifference = fmod(angleDifference + M_PI, 2 * M_PI) - M_PI;

            if (fabs(angleDifference) <= sensorAngle) {
                closestObstacleDistance = distance;
                lastObstacleAngle = angleToObstacle;
                obstacleDetected = true;
            }
        }
    }

    return obstacleDetected;
}


void AutonomousRobot::move(double maxWidth, double maxHeight) {
    if (detectObstacle()) {
        handleCollision();
    } else {
        double newX = position.first + velocity * cos(orientation * M_PI / 180.0);
        double newY = position.second + velocity * sin(orientation * M_PI / 180.0);

        // Проверяем, не выходит ли робот за границы сцены
        position.first = std::max(0.0, std::min(newX, maxWidth));
        position.second = std::max(0.0, std::min(newY, maxHeight));

        bool atEdge = false;
        if (newX < 0 || newX > maxWidth || newY < 0 || newY > maxHeight) {
            atEdge = true;
            newX = std::max(0.0, std::min(newX, maxWidth)); // Ограничиваем движение внутри рамок
            newY = std::max(0.0, std::min(newY, maxHeight));
        }

        // Если робот достиг края, обрабатываем это как столкновение
        if (atEdge) {
            std::cout << "Robot reached the edge(" << newX << ", " << newY << ")" << std::endl;
            handleCollision();
        }
    }
}

void AutonomousRobot::rotate(double angle) {
    // Поворачиваем на заданный угол
    orientation += angle;
    orientation = fmod(orientation, 360.0);  // Удерживаем угол в пределах 0-360 градусов
}

void AutonomousRobot::handleCollision() {
    // При столкновении поворачиваем на avoidanceAngle градусов для избежания препятствия
    //std::cout << "Handling collision, current orientation: " << orientation << std::endl;
    rotate(avoidanceAngle);
}
