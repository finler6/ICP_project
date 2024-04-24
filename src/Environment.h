// Environment.h
#pragma once
#include <vector>
#include "Robot.h"
#include "Obstacle.h"

class Environment {
public:
    void addRobot(Robot* robot);
    void addObstacle(const Obstacle& obstacle);
    void update(); // Вызывается для обновления состояния среды

private:
    std::vector<Robot*> robots;
    std::vector<Obstacle> obstacles;
};
