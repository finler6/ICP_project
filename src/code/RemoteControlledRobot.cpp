#include "RemoteControlledRobot.h"
#include <cmath>
#include <iostream>
RemoteControlledRobot::RemoteControlledRobot(int id, std::pair<double, double> position, double velocity, double orientation, double size)
    : Robot(id, position, velocity, orientation, size), movingForward(false), rotateDirection(0) {}

void RemoteControlledRobot::move(double maxWidth, double maxHeight) {
    if (movingForward) {
        position.first += velocity * cos(orientation * M_PI / 180.0);
        position.second += velocity * sin(orientation * M_PI / 180.0);
    }
}

void RemoteControlledRobot::rotate(double angle) {
    orientation += angle;  
    orientation = fmod(orientation, 360.0); 
}

void RemoteControlledRobot::handleCollision() {
    movingForward = false;  
    std::cout << "Moving forward set to: " << movingForward << std::endl;
}

void RemoteControlledRobot::setMoveForward(bool move) {
    movingForward = move;
}

void RemoteControlledRobot::setRotateDirection(double angle) {
    orientation += angle;
    orientation = fmod(orientation, 360.0);
    std::cout << "Orientation set to: " << orientation << std::endl;
}
