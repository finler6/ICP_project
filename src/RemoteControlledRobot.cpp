#include "RemoteControlledRobot.h"
#include <cmath>

RemoteControlledRobot::RemoteControlledRobot(int id, std::pair<double, double> position, double velocity, double orientation, double size)
    : Robot(id, position, velocity, orientation, size), movingForward(false), rotateDirection(0) {}

void RemoteControlledRobot::move() {
    if (movingForward) {
        // Расчет новой позиции на основе текущей скорости и ориентации
        position.first += velocity * cos(orientation * M_PI / 180.0);
        position.second += velocity * sin(orientation * M_PI / 180.0);
    }
}

void RemoteControlledRobot::rotate(double angle) {
    orientation += angle;  // Обновление угла ориентации
    orientation = fmod(orientation, 360.0);  // Удерживаем угол в пределах 0-360 градусов
}

void RemoteControlledRobot::handleCollision() {
    movingForward = false;  // Остановить движение вперед при столкновении
}

void RemoteControlledRobot::setMoveForward(bool move) {
    movingForward = move;
}

void RemoteControlledRobot::setRotateDirection(double angle) {
    rotateDirection = angle;
    rotate(rotateDirection);
}
