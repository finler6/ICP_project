#pragma once
#include "Robot.h"
#include "Environment.h"

class AutonomousRobot : public Robot {
public:
    AutonomousRobot(int id, std::pair<double, double> position, double velocity, double orientation, double sensorRange, Environment* env);
    void move(double maxWidth, double maxHeight) override;
    void rotate(double angle) override;
    void handleCollision() override;
    bool detectObstacle();
    double getSensorRange() const { return sensorRange; }

private:
    double avoidanceAngle;  // Угол поворота при обнаружении препятствия
    // Указатель на окружение, в котором находится робот
    Environment* environment;

    double sensorRange;  // Диапазон сенсор
    double lastObstacleAngle;  // Угол к последнему обнаруженному препятствию
};
