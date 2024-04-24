#include "SimulationEngine.h"
#include <thread>

SimulationEngine::SimulationEngine(Environment* environment)
    : environment(environment), running(false) {}

SimulationEngine::~SimulationEngine() {
    stop();
}

void SimulationEngine::start() {
    running = true;
    lastUpdate = std::chrono::steady_clock::now();
    while (running) {
        auto now = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdate);
        if (duration.count() >= 16) {  // Обновление каждые ~16 мс, что соответствует приблизительно 60 кадрам в секунду
            update();
            lastUpdate = now;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));  // Уменьшаем загрузку процессора
    }
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
    // Вычисляем время, прошедшее с последнего обновления
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedSeconds = currentTime - lastUpdateTime;
    lastUpdateTime = currentTime;

    // Обновляем состояние всех роботов и обрабатываем столкновения
    environment->update(elapsedSeconds.count());

    // Проверяем условия завершения симуляции
    if (checkEndConditions()) {
        emit simulationEnded();
        return;
    }

    // Запускаем следующее обновление через задержку, соответствующую временному шагу
    QTimer::singleShot(timeStep * 1000, this, &SimulationEngine::update);
}

bool SimulationEngine::checkEndConditions() {
    // Здесь можно определить условия завершения симуляции, например:
    // - Все роботы достигли своих целей
    // - Прошло определённое время
    // - Произошло определённое количество столкновений
    // Это место для вашей логики определения окончания симуляции
    return false; // По умолчанию симуляция не завершается
}

