#pragma once
#include "Environment.h"
#include <chrono>

class SimulationEngine {
public:
    SimulationEngine(Environment* environment);
    ~SimulationEngine();

    void start();   // Запуск симуляции
    void pause();   // Пауза симуляции
    void resume();  // Продолжение симуляции
    void stop();    // Остановка симуляции

private:
    Environment* environment;
    bool running;
    std::chrono::steady_clock::time_point lastUpdate;

    void update();  // Обновление симуляции
};