/**
 * @file Robot.h
 * @brief Abstract base class for Robot, providing fundamental attributes and functionalities for different robotic implementations.
 *
 * This class serves as a foundation for creating different types of robots by defining basic properties and mandatory operations such as movement, rotation, and collision handling.
 * @author Pavel Stepanov (xstepa77)
 * @author Gleb Litvinchuk (xlitvi02)
 * @date 2024-05-05
 */
#pragma once

#include "utility"
#include "cmath"
#include "iostream"
#include "QRectF"

class Robot {

public:
    /**
 * @brief Constructor for Robot class that initializes a new Robot instance.
 * @param id Unique identifier for the robot.
 * @param position Initial position of the robot represented as a pair (x-coordinate, y-coordinate).
 * @param velocity Initial velocity of the robot.
 * @param orientation Initial orientation of the robot in degrees.
 * @param sensorRange Range of the sensors attached to the robot.
 */
    Robot(int id, std::pair<double, double> position, double velocity, double orientation, double sensorRange);
    /**
 * @brief Virtual destructor for Robot class.
 */
    virtual ~Robot() = default;
    /**
 * @brief Pure virtual function to handle collision scenarios.
 */
    virtual void handleCollision() = 0;
    /**
 * @brief Pure virtual function to rotate the robot by a specific angle.
 * @param angle The angle in degrees to rotate the robot.
 */
    virtual void rotate(double angle) = 0;
    /**
 * @brief Pure virtual function to move the robot within a specified boundary.
 * @param maxWidth Maximum width of the environment.
 * @param maxHeight Maximum height of the environment.
 */
    virtual void move(double maxWidth, double maxHeight) = 0;
    /**
 * @brief Get the robot's unique identifier.
 * @return Integer representing the robot's ID.
 */

    [[nodiscard]] int getID() const { return id; }

    /**
 * @brief Check if the robot has completed its assigned task.
 * @return True if the task is completed, otherwise false.
 */
    [[nodiscard]] bool isTaskCompleted() const;

    /**
     * @brief Get the current speed of the robot.
     * @return The speed of the robot.
     */
    [[nodiscard]] double getSpeed() const;
    /**
 * @brief Get the range of the robot's sensors.
 * @return The sensor range in units.
 */
    [[nodiscard]] double getRange() const;
    /**
 * @brief Get the current orientation of the robot in degrees.
 * @return The orientation of the robot.
 */
    [[nodiscard]] double getOrientation() const;
    /**
 * @brief Set a new speed for the robot.
 * @param speed The new speed in units per second.
 */
    [[nodiscard]] double getSensorRange() const {return sensorRange;}

    void setSpeed(double speed);
    /**
 * @brief Set a new sensor range for the robot.
 * @param sensorSize The new size of the sensor range.
 */
    void setSensorSize(double sensorSize);
    /**
 * @brief Set a new orientation for the robot.
 * @param orientation The new orientation in degrees.
 */
    void setOrientation(double orientation);
    /**
 * @brief Set a new position for the robot.
 * @param position A pair of double values representing the new position (x, y) of the robot.
 */
    void setPosition(const std::pair<double, double>& position);
    /**
 * @brief Get the current position of the robot.
 * @return A pair representing the x and y coordinates of the robot.
 */

    [[nodiscard]] std::pair<double, double> getPosition() const;

private:
    bool taskCompleted = false; ///< Indicates whether the robot's current task has been completed.

protected:
    int id; ///< Unique identifier for the robot.
    double velocity; ///< Current speed of the robot.
    double orientation; ///< Current orientation of the robot in degrees.
    double sensorRange; ///< Range of the sensors equipped on the robot.
    std::pair<double, double> position; ///< Current position of the robot as (x, y) coordinates.
};
