/**
 * @file Obstacle.cpp
 * @brief Implements the Obstacle class defined in Obstacle.h.
 *
 * Provides detailed implementations of the constructor, getters, and setters for the Obstacle class.
  * @author Pavel Stepanov (xstepa77)
 * @author Gleb Litvinchuk (xlitvi02)
 * @date 2024-05-05
 */

#include "Obstacle.h"

/**
 * @brief Constructs an Obstacle object and logs its creation.
 * @param id The identifier for the obstacle.
 * @param position The initial position of the obstacle.
 * @param size The size of the obstacle.
 *
 * This constructor initializes the Obstacle with the given ID, position, and size, and logs the creation details.
 */
Obstacle::Obstacle(int id, std::pair<double, double> position, double size)
        : id(id), size(size), position(position) {
    std::cout << "Obstacle created with ID: " << id << ", at (" << position.first << ", " << position.second << ") with size " << size << std::endl;
}

/**
 * @brief Retrieves the ID of the obstacle.
 * @return The ID of the obstacle as an integer.
 */
int Obstacle::getId() const {
    return id;
}

/**
 * @brief Retrieves the current position of the obstacle.
 * @return A pair representing the x and y coordinates of the obstacle.
 */
std::pair<double, double> Obstacle::getPosition() const {
    return position;
}

/**
 * @brief Calculates and returns the bounding box of the obstacle.
 * @return A QRectF representing the rectangular bounds of the obstacle.
 *
 * This method calculates the bounding rectangle based on the obstacle's position and size.
 */
QRectF Obstacle::getBounds() const {
    double halfSize = size / 2.0;
    return QRectF(position.first - halfSize, position.second - halfSize, size, size);
}

/**
 * @brief Sets a new position for the obstacle.
 * @param position A new pair of x and y coordinates for the obstacle.
 */
void Obstacle::setPosition(const std::pair<double, double>& position) {
    this->position = position;
}

void Obstacle::setSize(double newSize) {
    this->size = newSize;
}