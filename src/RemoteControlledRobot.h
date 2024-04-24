#pragma once
#include "Robot.h"

class RemoteControlledRobot : public Robot {
public:
    RemoteControlledRobot(int id, std::pair<double, double> position, double velocity, double orientation, double size);
    void move() override;
    void rotate(double angle) override;
    void handleCollision() override;

    // Дополнительные методы для управления роботом
    void setMoveForward(bool move);
    void setRotateDirection(double angle);

private:
    bool movingForward;  // Флаг для контроля движения вперед
    double rotateDirection;  // Угол поворота (положительный для поворота по часовой стрелке, отрицательный - против)
};
