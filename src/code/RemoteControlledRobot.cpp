/**
 * @file AutonomousRobot.cpp
 * @brief Definition of the AutonomousRobot class, which extends the Robot base class with specific functionalities for autonomous navigation and obstacle detection.
 *
 * @author Pavel Stepanov (xstepa77)
 * @author Gleb Litvinchuk (xlitvi02)
 * @date 2024-05-05
 */
#include "RemoteControlledRobot.h"

/**
 * @brief Constructor for the AutonomousRobot class.
 * @param id The unique identifier for the robot.
 * @param position The initial position of the robot.
 * @param velocity The velocity of the robot.
 * @param orientation The orientation of the robot.
 * @param sensorRange The range of the robot's sensors.
 * @param env A pointer to the simulation environment.
 */
RemoteControlledRobot::RemoteControlledRobot(int id, std::pair<double, double> position, double velocity, double orientation, double sensorRange, Environment* env)
        : Robot(id, position, velocity, orientation, sensorRange), environment(env), currentSpeed(velocity), avoidanceAngle(orientation), movingForward(false), movingBackward(false), turningLeft(false), turningRight(false) {
    if (!environment) {
        std::cerr << "Environment pointer is null" << std::endl;
    }
}
/**
 * @brief Handle a collision with an obstacle.
 */
void RemoteControlledRobot::handleCollision() {
    // Заглушка
}
/**
 * @brief Move the robot in the simulation environment.
 * @param maxWidth The maximum width of the simulation environment.
 * @param maxHeight The maximum height of the simulation environment.
 */
void RemoteControlledRobot::move(double maxWidth, double maxHeight) {
    double radianOrientation = orientation * M_PI / 180.0;
    double proposedX = position.first + currentSpeed * cos(radianOrientation);
    double proposedY = position.second + currentSpeed * sin(radianOrientation);

    double actualX = position.first;
    double actualY = position.second;

    /// Check if the robot can move to the proposed position
    if (canMoveTo(proposedX, position.second, maxWidth, maxHeight)) {
        actualX = proposedX;
    } else {
        double stepX = (proposedX > position.first ? 1 : -1) * 0.5;
        /// Try to move the robot along the x-axis until it reaches the obstacle
        for (double nextX = position.first; fabs(nextX - position.first) <= fabs(currentSpeed); nextX += stepX) {
            if (!canMoveTo(nextX, position.second, maxWidth, maxHeight)) {
                break;
            }
            actualX = nextX;
        }
    }

    /// Check if the robot can move to the proposed position
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
    /// Update the robot's position
    if (actualX != position.first || actualY != position.second) {
        updatePosition(actualX, actualY, maxWidth, maxHeight);
    }
}

/**
 * @brief Update the robot's state based on the received commands.
 * @param command The command received from the user interface.
 */
void RemoteControlledRobot::update() {
    if (movingForward) {
        moveForward();
    } else if (movingBackward) {
        moveBackward();
    } else {
        currentSpeed = 0;
    }

    if (turningLeft) {
        turnLeft();
    } else if (turningRight) {
        turnRight();
    }
}
/**
 * @brief Rotate the robot by a specified angle.
 * @param angle The angle by which to rotate the robot.
 */
void RemoteControlledRobot::rotate(double angle) {
    orientation += angle;
    orientation = fmod(orientation, 360.0);
}
/**
 * @brief Move the robot forward.
 */
void RemoteControlledRobot::moveForward() {
    currentSpeed = velocity;
}
/**
 * @brief Move the robot backward.
 */
void RemoteControlledRobot::moveBackward() {
    currentSpeed = -velocity;
}
/**
 * @brief Turn the robot to the left.
 */
void RemoteControlledRobot::turnLeft() {
    rotate(-1 * avoidanceAngle);
}
/**
 * @brief Turn the robot to the right.
 */
void RemoteControlledRobot::turnRight() {
    rotate(avoidanceAngle);
}
/**
 * @brief Process a command received from the user interface.
 * @param command The command received from the user interface.
 */
void RemoteControlledRobot::processCommand(const QString &command) {
    if (command == "start_move_forward") {
        movingForward = true;
    } else if (command == "stop_move_forward") {
        movingForward = false;
    } else if (command == "start_move_backward") {
        movingBackward = true;
    } else if (command == "stop_move_backward") {
        movingBackward = false;
    } else if (command == "start_turn_left") {
        turningLeft = true;
    } else if (command == "stop_turn_left") {
        turningLeft = false;
    } else if (command == "start_turn_right") {
        turningRight = true;
    } else if (command == "stop_turn_right") {
        turningRight = false;
    }
}
/**
 * @brief Update the robot's position based on the new coordinates.
 * @param newX The new x-coordinate of the robot.
 * @param newY The new y-coordinate of the robot.
 * @param maxWidth The maximum width of the simulation environment.
 * @param maxHeight The maximum height of the simulation environment.
 */
void RemoteControlledRobot::updatePosition(double newX, double newY, double maxWidth, double maxHeight) {
    position.first = std::max(0.0, std::min(newX, maxWidth));
    position.second = std::max(0.0, std::min(newY, maxHeight));
}
/**
 * @brief Check if the robot can move to a specified position.
 * @param x The x-coordinate of the proposed position.
 * @param y The y-coordinate of the proposed position.
 * @param maxWidth The maximum width of the simulation environment.
 * @param maxHeight The maximum height of the simulation environment.
 * @return True if the robot can move to the specified position, otherwise false.
 */
bool RemoteControlledRobot::canMoveTo(double x, double y, double maxWidth, double maxHeight) {
    if (x < 0 || x > maxWidth || y < 0 || y > maxHeight) {
        return false;
    }

    int radius = 11;
    /// Check if the robot intersects with the environment boundaries
    for (const auto& obstacle : environment->getObstacles()) {
        QRectF obstacleBounds = obstacle->getBounds().adjusted(-radius, -radius, radius, radius);
        if (lineIntersectsRect(position.first, position.second, x, y, obstacleBounds)) {
            return false;
        }
    }
    /// Check if the robot intersects with other robots
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
 * @brief Check if a line intersects with a rectangle.
 * @param x1 The x-coordinate of the starting point of the line.
 * @param y1 The y-coordinate of the starting point of the line.
 * @param x2 The x-coordinate of the ending point of the line.
 * @param y2 The y-coordinate of the ending point of the line.
 * @param rect The rectangle to check for intersection.
 * @return True if the line intersects with the rectangle, otherwise false.
 */
bool RemoteControlledRobot::lineIntersectsRect(double x1, double y1, double x2, double y2, const QRectF& rect) {
    double left = rect.left();
    double right = rect.right();
    double top = rect.top();
    double bottom = rect.bottom();

    /// Check if the line intersects with any of the four sides of the rectangle
    return (lineIntersectsLine(x1, y1, x2, y2, left, top, right, top) ||
            lineIntersectsLine(x1, y1, x2, y2, left, bottom, right, bottom) ||
            lineIntersectsLine(x1, y1, x2, y2, left, top, left, bottom) ||
            lineIntersectsLine(x1, y1, x2, y2, right, top, right, bottom));
}

/**
 * @brief Check if two lines intersect.
 * @param x1 The x-coordinate of the starting point of the first line.
 * @param y1 The y-coordinate of the starting point of the first line.
 * @param x2 The x-coordinate of the ending point of the first line.
 * @param y2 The y-coordinate of the ending point of the first line.
 * @param x3 The x-coordinate of the starting point of the second line.
 * @param y3 The y-coordinate of the starting point of the second line.
 * @param x4 The x-coordinate of the ending point of the second line.
 * @param y4 The y-coordinate of the ending point of the second line.
 * @return True if the two lines intersect, otherwise false.
 */
bool RemoteControlledRobot::lineIntersectsLine(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
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
