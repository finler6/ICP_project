#pragma once
#include "Robot.h"
#include "Environment.h"
#include <utility>

class AutonomousRobot : public Robot {
public:
    AutonomousRobot(int id, std::pair<double, double> position, double velocity,
                    double orientation, double sensorRange, double maxWidth, double maxHeight, Environment* env);
    void move(double maxWidth, double maxHeight) override;

    void handleCollision() override;
    bool detectObstacle(double maxWidth, double maxHeight);

private:
    double maxWidth_;
    double maxHeight_;
    double avoidanceAngle;  // Угол поворота при обнаружении препятствия
    // Указатель на окружение, в котором находится робот
    Environment* environment;
    void rotate(double angle) override;
    double sensorRange;  // Диапазон сенсор
    double lastObstacleAngle;  // Угол к последнему обнаруженному препятствию
    void updatePosition(double newX, double newY, double maxWidth, double maxHeight);
    bool isEdgeWithinSensorRange(double maxWidth, double maxHeight);
    bool isWithinSensorRange(const Obstacle& obstacle);
    bool checkBoundary(double x, double y, double maxWidth, double maxHeight);
    void tryMove(double maxWidth, double maxHeight);
    void resolveAlongObstacle(double newX, double newY, double radianOrientation, double maxWidth, double maxHeight);
    bool canMoveTo(double x, double y, double maxWidth, double maxHeight);
    bool isObstacleAt(double x, double y);
    bool lineIntersectsRect(double x1, double y1, double x2, double y2, const QRectF& rect);
    bool lineIntersectsLine(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
    bool isOnLine(double x, double y, double x0, double y0);
    double radius;
};
