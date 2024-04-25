#include "Environment.h"
#include "RemoteControlledRobot.h"
#include "AutonomousRobot.h"
#include <cmath>


Environment::Environment() {}

Environment::~Environment() {
    clear();
}

void Environment::addRobot(Robot* robot) {
    robots.push_back(robot);
}
std::vector<Robot*>& Environment::getRobots() {
    return robots;
}

int Environment::getCollisionCount() const {
    return collisionCount;
}

void Environment::addObstacle(const Obstacle& obstacle) {
    obstacles.push_back(obstacle);
}

void Environment::update() {
    double maxWidth = 800.0; // Пример ширины рабочей области
    double maxHeight = 600.0; // Пример высоты рабочей области

    for (auto& robot : robots) {
        robot->move(maxWidth, maxHeight);
        checkCollisions(robot);
    }
}

void Environment::clear() {
    // Удаление всех роботов
    for (auto* robot : robots) {
        delete robot;
    }
    robots.clear();
    obstacles.clear();
}

bool Environment::checkCollisions(Robot* robot) {
    // Проверка столкновений робота с каждым препятствием
    bool collisionDetected = false;
    for (const auto& obstacle : obstacles) {
        if (isCollision(robot->getPosition(), robot->getSize(), obstacle.getPosition(), obstacle.getSize())) {
            robot->handleCollision(); // Метод для обработки столкновения
            collisionDetected = true;
            break;
        }
    }
    return collisionDetected;
}

bool Environment::isCollision(const std::pair<double, double>& pos1, double size1, const std::pair<double, double>& pos2, double size2) const {
    // Вычисление расстояния между центрами кругов
    double dx = pos1.first - pos2.first;
    double dy = pos1.second - pos2.second;
    double distance = sqrt(dx * dx + dy * dy);
    return distance < (size1 + size2); // Проверка перекрытия кругов
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
        iss >> type; // Read the type of the object (Robot or Obstacle)

        if (type == "Robot") {
            std::string robotType;
            int id;
            double x, y, speed, direction, sensor_range;

            iss >> robotType >> id >> x >> y >> speed >> direction >> sensor_range;
            Robot* robot = nullptr;

            if (robotType == "autonomous") {
                robot = new AutonomousRobot(id, {x, y}, speed, direction, sensor_range);
            } else if (robotType == "remote") {
                robot = new RemoteControlledRobot(id, {x, y}, speed, direction, sensor_range);
            }

            if (robot) {
                addRobot(robot);
            }
        } else if (type == "Obstacle") {
            double x, y, size;
                if (iss >> x >> y >> size) {
                    addObstacle(Obstacle({x, y}, size));
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

