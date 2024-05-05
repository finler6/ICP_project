/**
 * @file AutonomousRobot.cpp
 * @brief Definition of the AutonomousRobot class, which extends the Robot base class with specific functionalities for autonomous navigation and obstacle detection.
 *
 * @author Pavel Stepanov (xstepa77)
 * @author Gleb Litvinchuk (xlitvi02)
 * @date 2024-05-05
 */
#include "SimulationEngine.h"
#include "Obstacle.h"

/**
 * @brief Constructs a new SimulationEngine object with the specified parent.
 * @param environment The environment in which the simulation takes place.
 * @param parent The parent object of the simulation engine.
 */
SimulationEngine::SimulationEngine(Environment* environment, QObject* parent)
    : QObject(parent), environment(environment), timer(nullptr), running(false), timeStep(0.016) {
    startTime = std::chrono::steady_clock::now();
    lastUpdate = std::chrono::steady_clock::now();
}

SimulationEngine::~SimulationEngine() {
    stop();
    delete timer;  
}

/**
 * @brief Starts the simulation engine.
 */
void SimulationEngine::start() {
    if (running) return;  
    running = true;
    if (!timer) {
        timer = new QTimer(this);  
        connect(timer, &QTimer::timeout, this, &SimulationEngine::update);
    }
    timer->start(static_cast<int>(timeStep * 1000));  
}

/**
 * @brief Pauses the simulation engine.
 */
void SimulationEngine::pause() {
    running = false;
}

/**
 * @brief Resumes the simulation engine.
 */
void SimulationEngine::resume() {
    running = true;
    lastUpdate = std::chrono::steady_clock::now();
}

/**
 * @brief Stops the simulation engine.
 */
void SimulationEngine::stop() {
    running = false;
    if (timer) {
        timer->stop();  
    }
}

/**
 * @brief Updates the simulation engine.
 */
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
        RemoteControlledRobot* rcr = dynamic_cast<RemoteControlledRobot*>(robot.get());
        if (rcr) {
            rcr->update();
        }
    }

    emit updateGUI();
    lastUpdate = now;
}

/**
 * @brief Returns the robots in the environment.
 * @return A vector of pointers to the robots in the environment.
 */
std::vector<Robot*> SimulationEngine::getRobots() const {
    std::vector<Robot*> vec;
    for (const auto& robotPtr : environment->getRobots()) {
        vec.push_back(robotPtr.get());
    }
    return vec;
}

/**
 * @brief Returns the obstacles in the environment.
 * @return A vector of pointers to the obstacles in the environment.
 */
std::vector<Obstacle*> SimulationEngine::getObstacles() const {
    std::vector<Obstacle*> vec;
    for (const auto& obstacle : environment->getObstacles()) {
        vec.push_back(obstacle.get());
    }
    return vec;
}

/**
 * @brief Adds a robot to the environment.
 * @param type The type of the robot to add.
 * @param id The ID of the robot to add.
 * @param position The position of the robot to add.
 * @param speed The speed of the robot to add.
 * @param orientation The orientation of the robot to add.
 * @param sensorSize The sensor size of the robot to add.
 */
void SimulationEngine::addRobot(const QString& type, int id, const QPointF& position, double speed, double orientation, double sensorSize) {
    std::unique_ptr<Robot> robot;
    double maxWidth = 800;
    double maxHeight = 600;
    if (type == "autonomous") {
        robot = std::make_unique<AutonomousRobot>(id, std::make_pair(position.x(), position.y()), speed, orientation, sensorSize, maxWidth, maxHeight, environment);
    } else {
        robot = std::make_unique<RemoteControlledRobot>(id, std::make_pair(position.x(), position.y()), speed, orientation, sensorSize, environment);
    }
    environment->addRobot(std::move(robot));
}

/**
 * @brief Adds an obstacle to the environment.
 * @param id The ID of the obstacle to add.
 * @param position The position of the obstacle to add.
 * @param size The size of the obstacle to add.
 */
void SimulationEngine::addObstacle(int id, const QPointF& position, double size) {
    auto obstacle = std::make_unique<Obstacle>(id, std::make_pair(position.x(), position.y()), size);
    environment->addObstacle(std::move(obstacle));
}

/**
 * @brief Updates the robot with the specified ID.
 * @param id The ID of the robot to update.
 * @param speed The speed of the robot.
 * @param orientation The orientation of the robot.
 * @param sensorSize The sensor size of the robot.
 * @param x The x-coordinate of the robot.
 * @param y The y-coordinate of the robot.
 */
void SimulationEngine::updateRobot(int id, double speed, double orientation, double sensorSize, double x, double y) {
    Robot* robot = getRobotById(id);
    if (robot) {
        robot->setSpeed(speed);
        robot->setOrientation(orientation);
        robot->setSensorSize(sensorSize);
        robot->setPosition(std::make_pair(x, y));
        qDebug() << "Updating robot with ID:" << id << " to speed:" << speed << ", orientation:" << orientation << ", sensorSize:" << sensorSize;
    } else {
        qDebug() << "No robot found with ID:" << id << ", update failed.";
    }
}

/**
 * @brief Finds a robot with the specified ID.
 * @param id The ID of the robot to find.
 * @return A pointer to the robot with the specified ID, or nullptr if no such robot exists.
 */
Robot* SimulationEngine::findRobotById(int id) {
    auto& robots = environment->getRobots();
    auto it = std::find_if(robots.begin(), robots.end(),
                           [id](const std::unique_ptr<Robot>& robot) { return robot->getID() == id; });
    return it != robots.end() ? it->get() : nullptr;
}

Robot* SimulationEngine::getRobotById(int id) {
    return findRobotById(id);
}

/**
 * @brief Updates the obstacle with the specified ID.
 * @param id The ID of the obstacle to update.
 * @param size The size of the obstacle.
 * @param x The x-coordinate of the obstacle.
 * @param y The y-coordinate of the obstacle.
 */
void SimulationEngine::updateObstacle(int id, double size, double x, double y) {
    Obstacle* obstacle = getObstacleById(id);
    if (obstacle) {
        qDebug() << "Updating obstacle with ID:" << id << " to size:" << size;
        obstacle->setSize(size);
        obstacle->setPosition(std::make_pair(x, y));
    } else {
        qDebug() << "No obstacle found with ID:" << id << ", update failed.";
    }
}

/**
 * @brief Finds an obstacle with the specified ID.
 * @param id The ID of the obstacle to find.
 * @return A pointer to the obstacle with the specified ID, or nullptr if no such obstacle exists.
 */
Obstacle* SimulationEngine::getObstacleById(int id) {
    return findObstacleById(id);
}

/**
 * @brief Finds an obstacle with the specified ID.
 * @param id The ID of the obstacle to find.
 * @return A pointer to the obstacle with the specified ID, or nullptr if no such obstacle exists.
 */
Obstacle* SimulationEngine::findObstacleById(int id) {
    auto it = std::find_if(environment->getObstacles().begin(), environment->getObstacles().end(),
                           [id](const std::unique_ptr<Obstacle>& obstacle) { return obstacle->getId() == id; });
    return it != environment->getObstacles().end() ? it->get() : nullptr;
}

/**
 * @brief Removes the robot with the specified ID.
 * @param id The ID of the robot to remove.
 */
void SimulationEngine::removeRobot(int id) {
    std::cout << "Available Robot IDs: ";
    for (const auto& robot : environment->getRobots()) {
        std::cout << robot->getID() << " ";
    }
    std::cout << std::endl;

    std::cout << "Attempting to remove robot with ID: " << id << std::endl;
    if (environment->removeRobot(id)) {
        std::cout << "Robot removed." << std::endl;
    } else {
        std::cout << "Robot not found." << std::endl;
    }
}

/**
 * @brief Removes the obstacle with the specified ID.
 * @param id The ID of the obstacle to remove.
 */
void SimulationEngine::removeObstacle(int id) {
    if (environment->removeObstacle(id)) {
        std::cout << "Obstacle removed." << std::endl;
    } else {
        std::cout << "Obstacle not found." << std::endl;
    }
}

/**
 * @brief Sends a command to the remote-controlled robots.
 * @param command The command to send.
 */
void SimulationEngine::sendCommand(const QString &command) {
    auto remoteRobots = environment->findRemoteControlledRobots();

    for (auto& rcr : remoteRobots) {
        if (rcr) {
            rcr->processCommand(command);
        }
    }
}
