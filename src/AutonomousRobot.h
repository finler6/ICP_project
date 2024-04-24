#pragma once
#include "Robot.h"

class AutonomousRobot : public Robot {
public:
    AutonomousRobot(int id, std::pair<double, double> position, double velocity, double orientation, double size);
    void move() override;
    void rotate(double angle) override;
    void handleCollision() override;

private:
    double avoidanceAngle;  // Угол поворота при обнаружении препятствия
};
