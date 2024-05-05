/**
 * @file AutonomousRobot.cpp
 * @brief Definition of the AutonomousRobot class, which extends the Robot base class with specific functionalities for autonomous navigation and obstacle detection.
 *
 * @author Pavel Stepanov (xstepa77)
 * @author Gleb Litvinchuk (xlitvi02)
 * @date 2024-05-05
 */
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#pragma once

#include "Robot.h"
#include "Obstacle.h"
#include "vector"
#include "cmath"
#include "memory"
#include "utility"
#include "string"
#include "fstream"
#include "sstream"
#include "iostream"

class RemoteControlledRobot;
/**
 * @brief The Environment class represents the simulation environment in which robots operate.
 *
 * The Environment class manages the robots and obstacles in the simulation, providing methods to add, remove, and interact with them.
 */
class Environment {
public:
    double width = 800.0; 
    double height = 600.0; 
    Environment();  
    ~Environment();  

    void clear();
    bool removeRobot(int id);
    bool removeObstacle(int id);

    void addRobot(std::unique_ptr<Robot> robot);
    std::vector<std::unique_ptr<Robot>>& getRobots();
    void loadConfiguration(const std::string& filename);
    void addObstacle(std::unique_ptr<Obstacle> obstacle);
    std::vector<RemoteControlledRobot*> findRemoteControlledRobots(); /// Find all remote controlled robots in the environment.
    [[nodiscard]] const std::vector<std::unique_ptr<Obstacle>>& getObstacles() const; /// Get a vector of all obstacles in the environment.


private:
    std::vector<std::unique_ptr<Robot>> robots; /// Vector of unique pointers to the robots in the environment.
    std::vector<std::unique_ptr<Obstacle>> obstacles; /// Vector of unique pointers to the obstacles in the environment.
};

#endif // ENVIRONMENT_H