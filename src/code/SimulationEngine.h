#ifndef SIMULATIONENGINE_H
#define SIMULATIONENGINE_H

#include <QObject>
#include <QList>
#include <vector>
#include <memory>
#include <algorithm>
#include <QTimer>
#include <chrono>
#include "Environment.h"
#include "Robot.h"      // Ensure these are correctly included
#include "Obstacle.h"   // Ensure these are correctly included
#include "AutonomousRobot.h"
#include "RemoteControlledRobot.h"

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
    void addRobot(const QString &type, int id, const QPointF &position, double speed, double orientation, double sensorRange);
    void addObstacle(int id, const QPointF &position, double size);

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
    std::vector<std::unique_ptr<Robot>> robots;
    std::vector<Obstacle> obstacles;
};

#endif // SIMULATIONENGINE_H
