#include "Environment.h"
#include <cmath>

Environment::Environment() {}

Environment::~Environment() {
    clear();
}

void Environment::addRobot(Robot* robot) {
    robots.push_back(robot);
}

void Environment::addObstacle(const Obstacle& obstacle) {
    obstacles.push_back(obstacle);
}

void Environment::update() {
    for (auto& robot : robots) {
        robot->move();
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

void Environment::checkCollisions(Robot* robot) {
    // Проверка столкновений робота с каждым препятствием
    for (const auto& obstacle : obstacles) {
        if (isCollision(robot->getPosition(), robot->getSize(), obstacle.getPosition(), obstacle.getSize())) {
            robot->handleCollision(); // Метод для обработки столкновения
        }
    }
}

bool Environment::isCollision(const std::pair<double, double>& pos1, double size1, const std::pair<double, double>& pos2, double size2) const {
    // Вычисление расстояния между центрами кругов
    double dx = pos1.first - pos2.first;
    double dy = pos1.second - pos2.second;
    double distance = sqrt(dx * dx + dy * dy);
    return distance < (size1 + size2); // Проверка перекрытия кругов
}

