/**
 * @file AutonomousRobot.cpp
 * @brief Definition of the AutonomousRobot class, which extends the Robot base class with specific functionalities for autonomous navigation and obstacle detection.
 *
 * @author Pavel Stepanov (xstepa77)
 * @author Gleb Litvinchuk (xlitvi02)
 * @date 2024-05-05
 */
#ifndef REMOTECONTROLLEDROBOT_H
#define REMOTECONTROLLEDROBOT_H

#include "Robot.h"
#include "cmath"
#include "QString"
#include "QDebug"
#include "Environment.h"

/**
 * @class RemoteControlledRobot
 * @brief Represents a robot that can be controlled remotely through commands.
 *
 * This class extends the Robot class and provides additional functionalities to control the robot's movement and orientation remotely.
 */
class RemoteControlledRobot : public Robot {
public:
    RemoteControlledRobot(int id, std::pair<double, double> position, double velocity, double orientation, double sensorRange, Environment* env);

    void update();

    void turnLeft();
    void turnRight();
    void moveForward();
    void moveBackward();

    void handleCollision() override;
    void rotate(double angle) override;
    void processCommand(const QString &command);
    void move(double maxWidth, double maxHeight) override;

private:
    Environment* environment;

    double currentSpeed;
    double avoidanceAngle;

    bool movingForward = false;
    bool movingBackward = false;
    bool turningLeft = false;
    bool turningRight = false;

    bool canMoveTo(double x, double y, double maxWidth, double maxHeight);
    void updatePosition(double newX, double newY, double maxWidth, double maxHeight);
    bool lineIntersectsRect(double x1, double y1, double x2, double y2, const QRectF& rect);
    bool lineIntersectsLine(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
};

#endif // REMOTECONTROLLEDROBOT_H
