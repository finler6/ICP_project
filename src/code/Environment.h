#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#pragma once

#include "Robot.h"
#include "Obstacle.h"
#include <vector>
#include <memory>
#include <utility>  
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Environment {
public:
    double width = 800.0; 
    double height = 600.0; 
    Environment();  
    ~Environment();  
    std::vector<Robot*>& getRobots();
    void loadConfiguration(const std::string& filename);
    void addRobot(Robot* robot);
    void addObstacle(const Obstacle& obstacle);
    void update();
    void clear();
    int getCollisionCount() const;
    const std::vector<Obstacle>& getObstacles() const;
    bool checkCollisions(Robot* robot);

private:
    int collisionCount;
    std::vector<Robot*> robots;
    std::vector<Obstacle> obstacles;;
    bool isCollision(const std::pair<double, double>& pos1, double size1, const std::pair<double, double>& pos2, double size2) const;
};

#endif // ENVIRONMENT_H