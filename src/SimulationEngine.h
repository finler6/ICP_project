#ifndef SIMULATIONENGINE_H
#define SIMULATIONENGINE_H

#include <QObject>
#include <QTimer>
#include <chrono>
#include "Environment.h"

class SimulationEngine : public QObject {
    Q_OBJECT

public:
    explicit SimulationEngine(Environment* environment, QObject* parent = nullptr);
    virtual ~SimulationEngine();

    void start();
    void pause();
    void resume();
    void stop();
    void update();
    bool checkEndConditions();

signals:
    void simulationEnded();

private:
    Environment* environment;
    bool running;
    std::chrono::steady_clock::time_point lastUpdate;
    std::chrono::steady_clock::time_point startTime;
    double timeStep;
};

#endif // SIMULATIONENGINE_H
