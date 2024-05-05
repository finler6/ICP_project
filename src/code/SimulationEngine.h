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
#include "Robot.h"      
#include "Obstacle.h"   
#include "AutonomousRobot.h"
#include "RemoteControlledRobot.h"

class SimulationEngine : public QObject {
    Q_OBJECT

public:
    explicit SimulationEngine(Environment* environment, QObject* parent = nullptr);
    virtual ~SimulationEngine();
    Obstacle* findObstacleById(int id);
    void start();
    void pause();
    void resume();
    void stop();
    void update();
    bool checkEndConditions();
    std::vector<Robot*> getRobots() const;
    std::vector<Obstacle*> getObstacles() const;
    Environment* getEnvironment() const { return environment; }
    void addRobot(const QString &type, int id, const QPointF &position, double speed, double orientation, double sensorRange);
    void addObstacle(int id, const QPointF &position, double size);
    void updateRobot(int id, double speed, double orientation, double sensorSize, double x, double y);
    void updateObstacle(int id, double size, double x, double y);
    Robot* findRobotById(int id);
    Robot* getRobotById(int id);
    void updateRobotView(int id);
    Obstacle* getObstacleById(int id);
    void removeRobot(int id);
    void removeObstacle(int id);
    void sendCommand(const QString &command);

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
    std::vector<std::unique_ptr<Obstacle>> obstacles;

};

#endif // SIMULATIONENGINE_H
