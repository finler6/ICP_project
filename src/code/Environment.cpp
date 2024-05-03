#include "Environment.h"
#include "RemoteControlledRobot.h"
#include "AutonomousRobot.h"
#include <cmath>


Environment::Environment() {}

Environment::~Environment() {
    for (auto robot : robots) {
        delete robot;  
    }
}


void Environment::addRobot(Robot* robot) {
    robots.push_back(robot);
}
std::vector<Robot*>& Environment::getRobots() {
    return robots;
}

void Environment::addObstacle(const Obstacle& obstacle) {
    obstacles.push_back(obstacle);
}

void Environment::clear() {
    for (auto* robot : robots) {
        delete robot;
    }
    robots.clear();
    obstacles.clear();
}

bool Environment::checkCollisions(Robot* robot) {
    bool collisionDetected = false;
    for (const auto& obstacle : obstacles) {
        if (isCollision(robot->getPosition(), robot->getRange(), obstacle.getPosition(), obstacle.getSize())) {
            robot->handleCollision(); 
            collisionDetected = true;
            break;
        }
    }
    return collisionDetected;
}

bool Environment::isCollision(const std::pair<double, double>& pos1, double size1, const std::pair<double, double>& pos2, double size2) const {
    double distance = sqrt(pow(pos1.first - pos2.first, 2) + pow(pos1.second - pos2.second, 2));
    return distance < size1 + size2; 
}

void Environment::loadConfiguration(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type; 

        if (type == "Robot") {
            std::string robotType;
            int id;
            double x, y, speed, direction, sensor_range;

            iss >> robotType >> id >> x >> y >> speed >> direction >> sensor_range;
            Robot* robot = nullptr;

            if (robotType == "autonomous") {
                robot = new AutonomousRobot(id, {x, y}, speed, direction, sensor_range, width, height, this);
            } else if (robotType == "remote") {
                robot = new RemoteControlledRobot(id, {x, y}, speed, direction, sensor_range);
            }

            if (robot) {
                addRobot(robot);
            }
        } else if (type == "Obstacle") {
            int id;
            double x, y, size;
                if (iss >> id >> x >> y >> size) {
                    addObstacle(Obstacle(id, {x, y}, size));
                } else {
                    std::cerr << "Failed to read Obstacle data: " << line << std::endl;
                }
        }
    }
    file.close();
}

const std::vector<Obstacle>& Environment::getObstacles() const {
    return obstacles;
}

