/**
 * @file AutonomousRobot.cpp
 * @brief Definition of the AutonomousRobot class, which extends the Robot base class with specific functionalities for autonomous navigation and obstacle detection.
 *
 * @author Pavel Stepanov (xstepa77)
 * @author Gleb Litvinchuk (xlitvi02)
 * @date 2024-05-05
 */
#pragma once
#include "Robot.h"
#include "Environment.h"
#include <utility>

/**
 * @brief The AutonomousRobot class represents a robot that can navigate autonomously in the simulation environment.
 *
 * The AutonomousRobot class extends the Robot base class with specific functionalities for autonomous navigation and obstacle detection.
 */

class AutonomousRobot : public Robot {
public:
    AutonomousRobot(int id, std::pair<double, double> position, double velocity,
                    double orientation, double sensorRange, double maxWidth, double maxHeight, Environment* env); /// Constructor for the AutonomousRobot class.

    void move(double maxWidth, double maxHeight) override; /// Move the robot in the simulation environment.
    void handleCollision() override; /// Handle a collision with an obstacle.
    bool detectObstacle(double maxWidth, double maxHeight); /// Detect obstacles in the robot's path.

private:
    Environment* environment; /// Pointer to the simulation environment.

    double maxWidth_;
    double maxHeight_;
    double avoidanceAngle;
    double radius;

    void rotate(double angle) override; /// Rotate the robot by a specified angle.
    void tryMove(double maxWidth, double maxHeight); /// Attempt to move the robot in the simulation environment.
    bool isEdgeWithinSensorRange(double maxWidth, double maxHeight); /// Check if the robot is near the edge of the simulation environment.
    bool canMoveTo(double x, double y, double maxWidth, double maxHeight); /// Check if the robot can move to a specified position.
    bool checkBoundary(double x, double y, double maxWidth, double maxHeight); /// Check if the robot is within the simulation environment boundaries.
    void updatePosition(double newX, double newY, double maxWidth, double maxHeight); /// Update the robot's position in the simulation environment.
    bool lineIntersectsRect(double x1, double y1, double x2, double y2, const QRectF& rect); /// Check if a line intersects a rectangle.
    bool lineIntersectsLine(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4); /// Check if two lines intersect.
};
