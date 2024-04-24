#include "SimulationEngine.h"
#include <ostream>
#include <iostream>
#include "Obstacle.h"
#include <thread>


SimulationEngine::SimulationEngine(Environment* environment, QObject* parent)
    : QObject(parent), environment(environment), running(false), timeStep(0.016) {
    startTime = std::chrono::steady_clock::now();
}

SimulationEngine::~SimulationEngine() {
    stop();
}

void SimulationEngine::start() {
    running = true;
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SimulationEngine::update);
    timer->start(static_cast<int>(timeStep * 1000));  // Запуск таймера с интервалом timeStep
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
}

void SimulationEngine::update() {
    if (!running) return;
    // Обновление логики симуляции
    if (checkEndConditions()) {
        emit simulationEnded();
        QTimer::singleShot(0, this, [&]() { running = false; });  // Останавливаем обновление
    } else {
        QTimer::singleShot(static_cast<int>(timeStep * 1000), this, &SimulationEngine::update);
    }
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


