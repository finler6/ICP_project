/**
 * @file AutonomousRobot.cpp
 * @brief Definition of the AutonomousRobot class, which extends the Robot base class with specific functionalities for autonomous navigation and obstacle detection.
 *
 * @author Pavel Stepanov (xstepa77)
 * @author Gleb Litvinchuk (xlitvi02)
 * @date 2024-05-05
 */
#include "Environment.h"
#include "RemoteControlledRobot.h"
#include "AutonomousRobot.h"

/**
 * @brief Constructor for the AutonomousRobot class.
 * @param id Unique identifier for the robot.
 * @param position Initial position of the robot as a pair (x, y).
 * @param velocity Initial speed of the robot.
 * @param orientation Initial orientation of the robot in degrees.
 * @param sensorRange Range of the sensors attached to the robot.
 * @param width Width of the environment.
 * @param height Height of the environment.
 * @param environment Pointer to the environment in which the robot operates.
 */
Environment::Environment() {}

Environment::~Environment() {
}

/**
 * @brief Add a robot to the environment.
 * @param robot Unique pointer to the robot to be added.
 */
void Environment::addRobot(std::unique_ptr<Robot> robot) {
    robots.push_back(std::move(robot));
}

/**
 * @brief Get a vector of all robots in the environment.
 * @return A vector of unique pointers to the robots in the environment.
 */
std::vector<std::unique_ptr<Robot>>& Environment::getRobots() {
    return robots;
}

/**
 * @brief Clear the environment of all robots and obstacles.
 */
void Environment::clear() {
    robots.clear();
    obstacles.clear();
}

/**
 * @brief Load the configuration of the environment from a file.
 * @param filename Name of the file containing the configuration.
 */
void Environment::loadConfiguration(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }
    /// Read the file line by line
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type; 

        if (type == "Robot") {
            std::string robotType;
            int id;
            double x, y, speed, direction, sensor_range;

            iss >> robotType >> id >> x >> y >> speed >> direction >> sensor_range; /// Read the robot data

            /// Check the type of the robot and create the appropriate object
            if (robotType == "autonomous") {
                addRobot(std::make_unique<AutonomousRobot>(id, std::make_pair(x, y), speed, direction, sensor_range, width, height, this));
            } else if (robotType == "remote") {
                addRobot(std::make_unique<RemoteControlledRobot>(id, std::make_pair(x, y), speed, direction, sensor_range,  this));
            }
        } else if (type == "Obstacle") { /// Read the obstacle data
            int id;
            double x, y, size;
                if (iss >> id >> x >> y >> size) {
                    addObstacle(std::make_unique<Obstacle>(id, std::make_pair(x, y), size)); /// Create the obstacle object
                } else {
                    std::cerr << "Failed to read Obstacle data: " << line << std::endl;
                }
        }
    }
    file.close();
}
/**
 * @brief Add an obstacle to the environment.
 * @param obstacle Unique pointer to the obstacle to be added.
 */
void Environment::addObstacle(std::unique_ptr<Obstacle> obstacle) {
    obstacles.push_back(std::move(obstacle));
}

/**
 * @brief Remove an obstacle from the environment.
 * @param id Unique identifier of the obstacle to be removed.
 * @return True if the obstacle was removed, false otherwise.
 */
bool Environment::removeObstacle(int id) {
    auto it = std::find_if(obstacles.begin(), obstacles.end(),
                           [id](const std::unique_ptr<Obstacle>& obstacle) { return obstacle->getId() == id; });
    if (it != obstacles.end()) {
        obstacles.erase(it);
        return true;
    }
    return false;
}

/**
 * @brief Remove a robot from the environment.
 * @param id Unique identifier of the robot to be removed.
 * @return True if the robot was removed, false otherwise.
 */
bool Environment::removeRobot(int id) {
    auto it = std::find_if(robots.begin(), robots.end(),
                           [id](const std::unique_ptr<Robot>& robot) { return robot->getID() == id; });
    if (it != robots.end()) {
        robots.erase(it);
        return true;
    }
    return false;
}

/**
 * @brief Get a vector of all obstacles in the environment.
 * @return A vector of unique pointers to the obstacles in the environment.
 */
const std::vector<std::unique_ptr<Obstacle>>& Environment::getObstacles() const {
    return obstacles;
}

/**
 * @brief Find all remote-controlled robots in the environment.
 * @return A vector of pointers to the remote-controlled robots.
 */
std::vector<RemoteControlledRobot*> Environment::findRemoteControlledRobots() {
    std::vector<RemoteControlledRobot*> remoteRobots;
    for (const auto& robot : robots) {
        RemoteControlledRobot* rcr = dynamic_cast<RemoteControlledRobot*>(robot.get());
        if (rcr) {
            remoteRobots.push_back(rcr);
        }
    }
    return remoteRobots;
}
