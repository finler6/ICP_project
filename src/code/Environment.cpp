#include "Environment.h"
#include "RemoteControlledRobot.h"
#include "AutonomousRobot.h"
#include <cmath>


Environment::Environment() {}

Environment::~Environment() {
}


void Environment::addRobot(std::unique_ptr<Robot> robot) {
    robots.push_back(std::move(robot));
}

std::vector<std::unique_ptr<Robot>>& Environment::getRobots() {
    return robots;
}

void Environment::clear() {
    robots.clear();
    obstacles.clear();
}

bool Environment::checkCollisions(Robot* robot) {
    for (const auto& obstacle : obstacles) {
        if (isCollision(robot->getPosition(), robot->getRange(), obstacle->getPosition(), obstacle->getSize())) {
            robot->handleCollision();
            return true;
        }
    }
    return false;
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
                addRobot(std::make_unique<AutonomousRobot>(id, std::make_pair(x, y), speed, direction, sensor_range, width, height, this));
            } else if (robotType == "remote") {
                addRobot(std::make_unique<RemoteControlledRobot>(id, std::make_pair(x, y), speed, direction, sensor_range));
            }
        } else if (type == "Obstacle") {
            int id;
            double x, y, size;
                if (iss >> id >> x >> y >> size) {
                    addObstacle(std::make_unique<Obstacle>(id, std::make_pair(x, y), size));
                } else {
                    std::cerr << "Failed to read Obstacle data: " << line << std::endl;
                }
        }
    }
    file.close();
}

void Environment::addObstacle(std::unique_ptr<Obstacle> obstacle) {
    obstacles.push_back(std::move(obstacle));
}

bool Environment::removeObstacle(int id) {
    auto it = std::find_if(obstacles.begin(), obstacles.end(),
                           [id](const std::unique_ptr<Obstacle>& obstacle) { return obstacle->getId() == id; });
    if (it != obstacles.end()) {
        obstacles.erase(it);
        return true;
    }
    return false;
}

bool Environment::removeRobot(int id) {
    auto it = std::find_if(robots.begin(), robots.end(),
                           [id](const std::unique_ptr<Robot>& robot) { return robot->getID() == id; });
    if (it != robots.end()) {
        robots.erase(it);
        return true;
    }
    return false;
}

const std::vector<std::unique_ptr<Obstacle>>& Environment::getObstacles() const {
    return obstacles;
}