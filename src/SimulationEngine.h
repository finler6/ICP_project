#ifndef SIMULATIONENGINE_H
#define SIMULATIONENGINE_H

#include <QObject>
#include <QList>
#include <vector>
#include <algorithm>
#include <QTimer>
#include <chrono>
#include "Environment.h"
#include "Robot.h"      // Ensure these are correctly included
#include "Obstacle.h"   // Ensure these are correctly included

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
    QList<Robot*> getRobots() const;
    QList<Obstacle*> getObstacles() const;
    Environment* getEnvironment() const { return environment; }

signals:
    void simulationEnded();
    void updateGUI();

private:
    Environment* environment;
    bool running;
    std::chrono::steady_clock::time_point lastUpdate;
    std::chrono::steady_clock::time_point startTime;
    double timeStep;
    QTimer* timer;
};

#endif // SIMULATIONENGINE_H
