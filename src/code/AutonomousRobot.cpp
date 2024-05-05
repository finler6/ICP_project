/**
 * @file AutonomousRobot.cpp
 * @brief Definition of the AutonomousRobot class, which extends the Robot base class with specific functionalities for autonomous navigation and obstacle detection.
 *
 * @author Pavel Stepanov (xstepa77)
 * @author Gleb Litvinchuk (xlitvi02)
 * @date 2024-05-05
 */

#include "AutonomousRobot.h"
#include "QDebug"
#include "cmath"
#include "iostream"
#include "QRectF"

/**
 * @brief Constructs an AutonomousRobot object.
 * @param id Identifier for the robot.
 * @param position Initial position as a pair (x, y).
 * @param velocity Initial velocity of the robot.
 * @param orientation Initial orientation in degrees.
 * @param sensorRange Range of the sensors in units.
 * @param maxWidth Maximum width of the operational environment.
 * @param maxHeight Maximum height of the operational environment.
 * @param env Pointer to the environment within which the robot operates.
 *
 * Initializes an autonomous robot with the given parameters and sets up its operational environment and boundaries.
 */
AutonomousRobot::AutonomousRobot(int id, std::pair<double, double> position, double velocity, double orientation, double sensorRange, double maxWidth, double maxHeight, Environment* env)
        : Robot(id, position, velocity, orientation, sensorRange), environment(env), maxWidth_(maxWidth), maxHeight_(maxHeight), avoidanceAngle(orientation), radius(10.0) {
    if (!environment) {
        std::cerr << "Environment pointer is null" << std::endl;
    }
}


/**
 * @brief Detects obstacles within the sensor range and the given boundaries.
 * @param maxWidth Maximum width of the operational area.
 * @param maxHeight Maximum height of the operational area.
 * @return True if an obstacle is detected within the range, otherwise false.
 *
 * This method checks for any obstacles within a specified angle and range using the robot's sensors. If an obstacle is detected, the function returns true.
 */
bool AutonomousRobot::detectObstacle(double maxWidth, double maxHeight) {
    double radianOrientation = getOrientation() * M_PI / 180.0;
    double robotRadius = 10.0;

    for (int angle = -30; angle <= 30; angle += 2) {
        double currentAngle = radianOrientation + angle * M_PI / 180.0;
        double projectedX = position.first + (sensorRange + robotRadius) * cos(currentAngle);
        double projectedY = position.second + (sensorRange + robotRadius) * sin(currentAngle);
        for (const auto& obstacle : environment->getObstacles()) {
            QRectF bounds = obstacle->getBounds().adjusted(-robotRadius, -robotRadius, robotRadius, robotRadius);
            if (lineIntersectsRect(position.first, position.second, projectedX, projectedY, bounds)) {
                return true;
            }
        }
        for (const auto& otherRobot : environment->getRobots()) {
            if (otherRobot->getID() != this->id) {
                QRectF otherRobotBounds(
                        otherRobot->getPosition().first - robotRadius,
                        otherRobot->getPosition().second - robotRadius,
                        robotRadius * 2, robotRadius * 2);
                if (lineIntersectsRect(position.first, position.second, projectedX, projectedY, otherRobotBounds)) {
                    return true;
                }
            }
        }
    }
    return isEdgeWithinSensorRange(maxWidth, maxHeight);
}

/**
 * @brief Checks if the robot is close to the edge of the operational area.
 * @param maxWidth Maximum width of the area.
 * @param maxHeight Maximum height of the area.
 * @return True if the robot is near the edge, otherwise false.
 *
 * This method determines whether any part of the robot is within a specified boundary from the edges of the operational environment.
 */
bool AutonomousRobot::isEdgeWithinSensorRange(double maxWidth, double maxHeight) {
    double x = position.first;
    double y = position.second;
    double orientationRad = getOrientation() * M_PI / 180.0;
    double sensorAngle = 15.0 * M_PI / 180.0;
    double centerX = x + sensorRange * cos(orientationRad);
    double centerY = y + sensorRange * sin(orientationRad);
    double leftX = x + sensorRange * cos(orientationRad - sensorAngle);
    double leftY = y + sensorRange * sin(orientationRad - sensorAngle);
    double rightX = x + sensorRange * cos(orientationRad + sensorAngle);
    double rightY = y + sensorRange * sin(orientationRad + sensorAngle);
    return checkBoundary(leftX, leftY, maxWidth, maxHeight) ||
           checkBoundary(centerX, centerY, maxWidth, maxHeight) ||
           checkBoundary(rightX, rightY, maxWidth, maxHeight);
}

/**
 * @brief Checks whether the proposed new position is within the boundaries of the operational area.
 * @param x The x-coordinate of the proposed new position.
 * @param y The y-coordinate of the proposed new position.
 * @param maxWidth The maximum allowed width of the area.
 * @param maxHeight The maximum allowed height of the area.
 * @return True if the new position is within the boundaries, false otherwise.
 *
 * This method checks whether a given position is within the defined boundaries of the operating environment.
 */
bool AutonomousRobot::checkBoundary(double x, double y, double maxWidth, double maxHeight) {
    return x <= 0 || x >= maxWidth || y <= 0 || y >= maxHeight;
}

/**
 * @brief Moves the robot within the environment, considering potential obstacles.
 * @param maxWidth Maximum width of the environment.
 * @param maxHeight Maximum height of the environment.
 *
 * This method attempts to move the robot based on its current velocity and orientation, checking for and responding to obstacles as needed.
 */
void AutonomousRobot::move(double maxWidth, double maxHeight) {
    if (detectObstacle(maxWidth, maxHeight)) {
        handleCollision();
        tryMove(maxWidth, maxHeight);
    } else {
        tryMove(maxWidth, maxHeight);
    }
}

/**
 * @brief Updates the robot's position to the new coordinates, ensuring it does not exceed the defined area limits.
 * @param newX Proposed new x-coordinate.
 * @param newY Proposed new y-coordinate.
 * @param maxWidth Maximum width of the operational area.
 * @param maxHeight Maximum height of the operational area.
 *
 * This method updates the position of the robot within the operational boundaries, correcting it if it goes beyond the limits.
 */
void AutonomousRobot::updatePosition(double newX, double newY, double maxWidth, double maxHeight) {
    position.first = std::max(0.0, std::min(newX, maxWidth));
    position.second = std::max(0.0, std::min(newY, maxHeight));
}

/**
 * @brief Rotates the robot by a specified angle.
 * @param angle The angle in degrees to rotate the robot.
 *
 * This method adjusts the orientation of the robot by adding the specified angle, ensuring the orientation wraps around at 360 degrees.
 */
void AutonomousRobot::rotate(double angle) {
    orientation += angle;
    orientation = fmod(orientation, 360.0);
}

/**
 * @brief Handles the collision by initiating an avoidance maneuver.
 *
 * This method is called when a collision is detected and typically involves rotating the robot to an angle meant to avoid the collision.
 */
void AutonomousRobot::handleCollision() {
    rotate(avoidanceAngle);
}

/**
 * @brief Attempts to move the robot to a new position, considering possible obstacles.
 * @param maxWidth The maximum width of the environment.
 * @param maxHeight The maximum height of the environment.
 *
 * This method computes a new proposed position based on the current orientation and velocity. It checks if the move is possible and adjusts the position step by step if necessary.
 */
void AutonomousRobot::tryMove(double maxWidth, double maxHeight) {
    double radianOrientation = orientation * M_PI / 180.0;
    double proposedX = position.first + velocity * cos(radianOrientation);
    double proposedY = position.second + velocity * sin(radianOrientation);

    double actualX = position.first;
    double actualY = position.second;

    if (canMoveTo(proposedX, position.second, maxWidth, maxHeight)) {
        actualX = proposedX;
    } else {
        double stepX = (proposedX > position.first ? 1 : -1) * 0.5;
        for (double nextX = position.first; fabs(nextX - position.first) <= fabs(velocity); nextX += stepX) {
            if (!canMoveTo(nextX, position.second, maxWidth, maxHeight)) {
                break;
            }
            actualX = nextX;
        }
    }

    if (canMoveTo(position.first, proposedY, maxWidth, maxHeight)) {
        actualY = proposedY;
    } else {
        double stepY = (proposedY > position.second ? 1 : -1) * 0.5;
        for (double nextY = position.second; fabs(nextY - position.second) <= fabs(velocity); nextY += stepY) {
            if (!canMoveTo(position.first, nextY, maxWidth, maxHeight)) {
                break;
            }
            actualY = nextY;
        }
    }

    if (actualX != position.first || actualY != position.second) {
        updatePosition(actualX, actualY, maxWidth, maxHeight);
    }
}


/**
 * @brief Determines if the robot can move to a specified location without colliding with obstacles or other robots.
 * @param x The x-coordinate of the proposed location.
 * @param y The y-coordinate of the proposed location.
 * @param maxWidth The maximum width of the environment.
 * @param maxHeight The maximum height of the environment.
 * @return True if the move is possible without collision, false otherwise.
 *
 * This method checks for the presence of obstacles and other robots at the proposed location, ensuring no collisions will occur if the robot moves there.
 */
bool AutonomousRobot::canMoveTo(double x, double y, double maxWidth, double maxHeight) {
    if (x < 0 || x > maxWidth || y < 0 || y > maxHeight) {
        return false;
    }

    for (const auto& obstacle : environment->getObstacles()) {
        QRectF obstacleBounds = obstacle->getBounds().adjusted(-radius, -radius, radius, radius);
        if (lineIntersectsRect(position.first, position.second, x, y, obstacleBounds)) {
            return false;
        }
    }

    for (const auto& otherRobot : environment->getRobots()) {
        if (otherRobot->getID() != this->id) {
            QRectF robotBounds(
                    otherRobot->getPosition().first - (2 *radius),
                    otherRobot->getPosition().second - (2 *radius),
                    2 * (2 *radius), 2 * (2 *radius));
            if (lineIntersectsRect(position.first, position.second, x, y, robotBounds)) {
                return false;
            }
        }
    }
    return true;
}


/**
 * @brief Checks if a line intersects with a rectangle.
 * @param x1 x-coordinate of the first point of the line.
 * @param y1 y-coordinate of the first point of the line.
 * @param x2 x-coordinate of the second point of the line.
 * @param y2 y-coordinate of the second point of the line.
 * @param rect The rectangle to check for intersection.
 * @return True if the line intersects with the rectangle, false otherwise.
 *
 * This method checks if any part of a line segment intersects with any of the four sides of a rectangle.
 */
bool AutonomousRobot::lineIntersectsRect(double x1, double y1, double x2, double y2, const QRectF& rect) {
    double left = rect.left();
    double right = rect.right();
    double top = rect.top();
    double bottom = rect.bottom();

    return (lineIntersectsLine(x1, y1, x2, y2, left, top, right, top) ||
            lineIntersectsLine(x1, y1, x2, y2, left, bottom, right, bottom) ||
            lineIntersectsLine(x1, y1, x2, y2, left, top, left, bottom) ||
            lineIntersectsLine(x1, y1, x2, y2, right, top, right, bottom));
}

/**
 * @brief Checks if two line segments intersect.
 * @param x1 x-coordinate of the start point of the first line.
 * @param y1 y-coordinate of the start point of the first line.
 * @param x2 x-coordinate of the end point of the first line.
 * @param y2 y-coordinate of the end point of the first line.
 * @param x3 x-coordinate of the start point of the second line.
 * @param y3 y-coordinate of the start point of the second line.
 * @param x4 x-coordinate of the end point of the second line.
 * @param y4 y-coordinate of the end point of the second line.
 * @return True if the lines intersect, false otherwise.
 *
 * This method calculates if two line segments intersect by determining if each line segment crosses the path of the other.
 */
bool AutonomousRobot::lineIntersectsLine(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
    double denominator = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);

    if (fabs(denominator) < 1e-6) {

        if ((y4 - y3) == 0) {
            if (y1 != y3) return false;
            return std::max(x1, x2) >= std::min(x3, x4) && std::min(x1, x2) <= std::max(x3, x4);
        } else if ((x4 - x3) == 0) {
            if (x1 != x3) return false;
            return std::max(y1, y2) >= std::min(y3, y4) && std::min(y1, y2) <= std::max(y3, y4);
        }
        return false;
    }

    double ua = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / denominator;
    double ub = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / denominator;

    return ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1;
}
