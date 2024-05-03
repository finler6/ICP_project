#include "code/SimulationEngine.h"
#include <ostream>
#include <iostream>
#include "code/Obstacle.h"
#include <thread>


SimulationEngine::SimulationEngine(Environment* environment, QObject* parent)
    : QObject(parent), environment(environment), running(false), timeStep(0.016), timer(nullptr) {
    startTime = std::chrono::steady_clock::now();
    lastUpdate = std::chrono::steady_clock::now();
}

SimulationEngine::~SimulationEngine() {
    stop();
    delete timer;  
}

void SimulationEngine::start() {
    if (running) return;  
    running = true;
    if (!timer) {
        timer = new QTimer(this);  
        connect(timer, &QTimer::timeout, this, &SimulationEngine::update);
    }
    timer->start(static_cast<int>(timeStep * 1000));  
}


void SimulationEngine::pause() {
    running = false;
}

void SimulationEngine::resume() {
    running = true;
    lastUpdate = std::chrono::steady_clock::now();
}

void SimulationEngine::stop() {
    running = false;
    if (timer) {
        timer->stop();  
    }
}

void SimulationEngine::update() {
    if (!running) return;

    double maxWidth = environment->width;
    double maxHeight = environment->height;
    auto now = std::chrono::steady_clock::now();
    double elapsedMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdate).count();

    if (elapsedMilliseconds < timeStep * 1000) {
        return; 
    }

    for (auto& robot : environment->getRobots()) {
        robot->move(maxWidth, maxHeight);
    }

    emit updateGUI();
    if (checkEndConditions()) {
        emit simulationEnded();
        QTimer::singleShot(0, this, [&]() { running = false; });
    } else {
        QTimer::singleShot(static_cast<int>(timeStep * 1000), this, &SimulationEngine::update);
    }
    lastUpdate = now;
}

bool SimulationEngine::checkEndConditions() {
    
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = currentTime - startTime; 
    if (duration.count() > 1800.0) { 
        std::cout << "Simulation ended due to time limit." << std::endl;
        return true;
    }

    
    bool allTasksCompleted = true;
    for (auto& robot : environment->getRobots()) { 
        if (!robot->isTaskCompleted()) {
            allTasksCompleted = false;
            return false;
        }
    }
    if (allTasksCompleted) {
        std::cout << "Simulation ended because all tasks are completed." << std::endl;
        return true;
    }

    
    if (environment->getCollisionCount() > 50) { 
        std::cout << "Simulation ended due to excessive collisions." << std::endl;
        return true;
    }

    return false; 
}

QList<Robot*> SimulationEngine::getRobots() const {
    std::vector<Robot*> vec = environment->getRobots();
    QList<Robot*> list;
    for (auto robot : vec) {
        list.append(robot);
    }
    return list;
}

QList<Obstacle*> SimulationEngine::getObstacles() const {
    std::vector<Obstacle> vec = environment->getObstacles();
    QList<Obstacle*> list;
    for (const Obstacle& obstacle : vec) {
        list.append(new Obstacle(obstacle));  
    }
    return list;
}

void SimulationEngine::addRobot(const QString& type, int id, const QPointF& position, double speed, double orientation, double sensorRange) {
    Robot* robot = nullptr;
    if (type == "autonomous") {
        if (!environment) {
            std::cerr << "SimulationEngine off" << std::endl;
            return;
        }
        robot = new AutonomousRobot(id, std::make_pair(position.x(), position.y()), speed, orientation, sensorRange, environment->width, environment->height, environment);
    } else if (type == "remote") {
        robot = new RemoteControlledRobot(id, std::make_pair(position.x(), position.y()), speed, orientation, sensorRange);
    }

    if (robot) {
        environment->addRobot(robot);
    }
}



void SimulationEngine::addObstacle(int id, const QPointF& position, double size) {
    Obstacle obstacle(id, std::make_pair(position.x(), position.y()), size);
    environment->addObstacle(obstacle);
}

void SimulationEngine::updateRobot(int id, double speed, double orientation, double sensorSize) {
    Robot* robot = findRobotById(id);
    if (robot) {
        robot->setSpeed(speed);
        robot->setOrientation(orientation);
        robot->setSensorSize(sensorSize);
    }
}


Robot* SimulationEngine::findRobotById(int id) {
    for (auto& robot : robots) { 
        if (robot->getID() == id) {
            return robot.get(); 
        }
    }
    return nullptr; 
}


Robot* SimulationEngine::getRobotById(int id) {
    return findRobotById(id); 
}

void SimulationEngine::updateObstacle(int id, double size) {
    for (auto& obstacle : obstacles) {
        if (obstacle.getId() == id) {
            obstacle.setSize(size);
            return;
        }
    }
}
Obstacle* SimulationEngine::getObstacleById(int id) {
    return findObstacleById(id);
}

Obstacle* SimulationEngine::findObstacleById(int id) {
    for (auto& obstacle : obstacles) {
        if (obstacle.getId() == id) {
            return &obstacle;
        }
    }
    return nullptr;
}





