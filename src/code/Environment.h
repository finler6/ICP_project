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

class RemoteControlledRobot;

class Environment {
public:
    double width = 800.0; 
    double height = 600.0; 
    Environment();  
    ~Environment();  
    std::vector<std::unique_ptr<Robot>>& getRobots();
    void loadConfiguration(const std::string& filename);
    void addRobot(std::unique_ptr<Robot> robot);
    void addObstacle(std::unique_ptr<Obstacle> obstacle);
    bool removeObstacle(int id);
    bool removeRobot(int id);
    void update();
    void clear();
    int getCollisionCount() const;
    const std::vector<std::unique_ptr<Obstacle>>& getObstacles() const;
    bool checkCollisions(Robot* robot);

    std::vector<RemoteControlledRobot*> findRemoteControlledRobots();

private:
    int collisionCount;
    std::vector<std::unique_ptr<Robot>> robots;
    std::vector<std::unique_ptr<Obstacle>> obstacles;
    bool isCollision(const std::pair<double, double>& pos1, double size1, const std::pair<double, double>& pos2, double size2) const;
};

#endif // ENVIRONMENT_H