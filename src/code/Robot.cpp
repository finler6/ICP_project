/**
 * @file Robot.cpp
 * @brief Definition of the Robot class which serves as a base class for different types of robotic functionalities.
 *
 * This class provides basic functionalities for a robot including operations to set and get position,
 * speed, orientation, and sensor range. It's designed to be inherited by more specialized robotic classes.
 * @author Pavel Stepanov (xstepa77)
 * @author Gleb Litvinchuk (xlitvi02)
 * @date 2024-05-05
 */

#include "Robot.h"

/**
 * @brief Constructor for the Robot class.
 * @param id Unique identifier for the robot.
 * @param position Initial position of the robot as a pair (x, y).
 * @param velocity Initial speed of the robot.
 * @param orientation Initial orientation of the robot in degrees.
 * @param sensorRange Range of the sensors attached to the robot.
 */
Robot::Robot(int id, std::pair<double, double> position, double velocity, double orientation, double sensorRange)
    : id(id), velocity(velocity), orientation(orientation), sensorRange(sensorRange), position(position) {}

/**
* @brief Get the current position of the robot.
* @return A pair representing the x and y coordinates of the robot.
*/
std::pair<double, double> Robot::getPosition() const {
    return position;
}

/**
 * @brief Get the current speed of the robot.
 * @return The speed of the robot.
 */
double Robot::getSpeed() const {
    return velocity;
}

/**
 * @brief Get the current orientation of the robot in degrees.
 * @return The orientation of the robot.
 */
double Robot::getOrientation() const {
    return orientation;
}

/**
 * @brief Get the range of the sensors of the robot.
 * @return The sensor range in units.
 */
double Robot::getRange() const {
    return sensorRange;
}

/**
 * @brief Set a new position for the robot.
 * @param position A pair of double values representing the new position (x, y) of the robot.
 */
void Robot::setPosition(const std::pair<double, double>& position) {
    this->position = position;
}

void Robot::setSpeed(double speed) {
    this->velocity = speed;
}

void Robot::setOrientation(double orientation) {
    this->orientation = orientation;
}

void Robot::setSensorSize(double sensorSize) {
    this->sensorRange = sensorSize;
}

/**
 * @brief Check if the robot has completed its assigned task.
 * @return True if the task is completed, otherwise false.
 */
bool Robot::isTaskCompleted() const {
    return taskCompleted;
}
