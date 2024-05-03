#pragma once
#include "Robot.h"

class RemoteControlledRobot : public Robot {
public:
    RemoteControlledRobot(int id, std::pair<double, double> position, double velocity, double orientation, double size);
    void move(double maxWidth, double maxHeight) override;
    void rotate(double angle) override;
    void handleCollision() override;
    void setMoveForward(bool move);
    void setRotateDirection(double angle);

private:
    bool movingForward;  
    double rotateDirection;  
};
