#pragma once

#include "Robot.h"
#include "Obstacle.h"
#include <vector>
#include <utility>  // Для std::pair
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Environment {
public:
    Environment();  // Конструктор
    ~Environment();  // Деструктор
    std::vector<Robot*>& getRobots();
    void loadConfiguration(const std::string& filename);
    void addRobot(Robot* robot);
    void addObstacle(const Obstacle& obstacle);
    void update();
    void clear();
    int getCollisionCount() const;
    const std::vector<Obstacle>& getObstacles() const;

private:
    int collisionCount;
    std::vector<Robot*> robots;
    std::vector<Obstacle> obstacles;
    void checkCollisions(Robot* robot);
    bool isCollision(const std::pair<double, double>& pos1, double size1, const std::pair<double, double>& pos2, double size2) const;
};

