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
    delete timer;  // Освобождаем память, выделенную для таймера
}

void SimulationEngine::start() {
    if (running) return;  // Предотвращение повторного запуска
    running = true;
    if (!timer) {
        timer = new QTimer(this);  // Создаем таймер, если он еще не создан
        connect(timer, &QTimer::timeout, this, &SimulationEngine::update);
    }
    timer->start(static_cast<int>(timeStep * 1000));  // Перезапускаем таймер
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
        timer->stop();  // Останавливаем таймер
    }
}

void SimulationEngine::update() {
    std::cout << "Update called" << std::endl;
    if (!running) return;

    double maxWidth = environment->width;
    double maxHeight = environment->height;
    auto now = std::chrono::steady_clock::now();
    double elapsedMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdate).count();

    if (elapsedMilliseconds < timeStep * 1000) {
        return; // Если с последнего обновления прошло меньше времени, чем заданный шаг в миллисекундах, то выходим из функции
    }

    for (auto& robot : environment->getRobots()) {
        robot->move(maxWidth, maxHeight);
        if (environment->checkCollisions(robot)) {  // Проверка на столкновения
            // Дополнительные действия после столкновения, если необходимо
        }
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
    // Проверяем временные ограничения (например, симуляция длится не более 30 минут)
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = currentTime - startTime; // startTime должен быть определен в классе и установлен при запуске симуляции
    if (duration.count() > 1800.0) { // 1800 секунд = 30 минут
        std::cout << "Simulation ended due to time limit." << std::endl;
        return true;
    }

    // Проверяем выполнение задач роботами (например, все роботы достигли целевых точек)
    bool allTasksCompleted = true;
    for (auto& robot : environment->getRobots()) { // Предполагаем, что у класса Environment есть метод getRobots, возвращающий список всех роботов
        if (!robot->isTaskCompleted()) { // Предполагаем, что у класса Robot есть метод isTaskCompleted, определяющий, выполнена ли его задача
            allTasksCompleted = false;
            return false;
        }
    }
    if (allTasksCompleted) {
        std::cout << "Simulation ended because all tasks are completed." << std::endl;
        return true;
    }

    // Проверяем наличие слишком многих столкновений, если это важно для симуляции
    if (environment->getCollisionCount() > 50) { // Предполагаем, что у класса Environment есть метод getCollisionCount
        std::cout << "Simulation ended due to excessive collisions." << std::endl;
        return true;
    }

    return false; // Если ни одно из условий не выполнено, продолжаем симуляцию
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
        list.append(new Obstacle(obstacle));  // Creating new pointers from objects
    }
    return list;
}

void SimulationEngine::addRobot(const QString& type, int id, const QPointF& position, double speed, double orientation, double sensorSize) {
    Robot* robot = nullptr;
    if (type == "autonomous") {
        robot = new AutonomousRobot(id, std::make_pair(position.x(), position.y()), speed, orientation, sensorSize);
    } else if (type == "remote") {
        robot = new RemoteControlledRobot(id, std::make_pair(position.x(), position.y()), speed, orientation, sensorSize);
    }

    if (robot) {
        environment->addRobot(robot);
    }
}



void SimulationEngine::addObstacle(int id, const QPointF& position, double size) {
    Obstacle obstacle(id, std::make_pair(position.x(), position.y()), size);
    environment->addObstacle(obstacle);
}



