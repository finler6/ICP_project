#ifndef REMOTECONTROLLEDROBOT_H
#define REMOTECONTROLLEDROBOT_H

#include "Robot.h"
#include "cmath"
#include <QString>
#include "QDebug"
#include "Environment.h"

class RemoteControlledRobot : public Robot {
public:
    RemoteControlledRobot(int id, std::pair<double, double> position, double velocity, double orientation, double sensorRange, double maxWidth, double maxHeight, Environment* env);
    void move(double maxWidth, double maxHeight) override;
    void rotate(double angle) override;
    void handleCollision() override;

    void processCommand(const QString &command); // Обработка команд
    void update();  // Метод обновления состояния робота, если он есть
    void moveForward();
    void moveBackward();
    void turnLeft();
    void turnRight();

private:
    double currentSpeed;
    double avoidanceAngle;

    bool movingForward = false;
    bool movingBackward = false;
    bool turningLeft = false;
    bool turningRight = false;

    Environment* environment;
    void updatePosition(double newX, double newY, double maxWidth, double maxHeight);
    void tryMove(double maxWidth, double maxHeight);
    bool canMoveTo(double x, double y, double maxWidth, double maxHeight);
    bool isObstacleAt(double x, double y);
    bool lineIntersectsRect(double x1, double y1, double x2, double y2, const QRectF& rect);
    bool lineIntersectsLine(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);

};

#endif // REMOTECONTROLLEDROBOT_H
