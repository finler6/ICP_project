/**
 * @file Obstacle.h
 * @brief Class to represent obstacles in a simulated environment.
 *
 * This class provides methods and properties to manage obstacles, including their size, position, and identification.
  * @author Pavel Stepanov (xstepa77)
 * @author Gleb Litvinchuk (xlitvi02)
 * @date 2024-05-05
 */

#ifndef OBSTACLE_H
#define OBSTACLE_H

#pragma once

#include "QRectF"
#include "utility"
#include "iostream"

/**
 * @class Obstacle
 * @brief Represents an obstacle with a specific position and size.
 *
 * This class provides functionality to get and set the properties of an obstacle, including its position, size, and ID.
 */
class Obstacle {
public:
    /**
     * @brief Constructor for an Obstacle object.
     * @param id An integer identifier for the obstacle.
     * @param position The initial position of the obstacle as a pair (x, y).
     * @param size The size of the obstacle.
     */
    Obstacle(int id, std::pair<double, double> position, double size);

    /**
     * @brief Get the ID of the obstacle.
     * @return The integer ID of the obstacle.
     */
    [[nodiscard]] int getId() const;

    /**
     * @brief Get the bounding rectangle of the obstacle.
     * @return A QRectF representing the bounds of the obstacle.
     */
    [[nodiscard]] QRectF getBounds() const;

    /**
     * @brief Set the size of the obstacle.
     * @param newSize The new size of the obstacle.
     */
    void setSize(double newSize);

    /**
     * @brief Get the position of the obstacle.
     * @return A pair representing the x and y coordinates of the obstacle's position.
     */
    [[nodiscard]] std::pair<double, double> getPosition() const;

    /**
     * @brief Set a new position for the obstacle.
     * @param position A pair representing the new x and y coordinates for the obstacle.
     */
    void setPosition(const std::pair<double, double>& position);

private:
    int id; ///< ID of the obstacle.
    double size; ///< Size of the obstacle.
    std::pair<double, double> position; ///< Position of the obstacle.
};

#endif // OBSTACLE_H


