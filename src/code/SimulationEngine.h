/**
 * @file SimulationEngine.h
 * @brief Class to manage the simulation environment for robotic operations.
 *
 * This class manages the simulation of an environment containing robots and obstacles. It provides functionality to control the simulation state and manipulate objects within the simulation.
 * @author Pavel Stepanov (xstepa77)
 * @author Gleb Litvinchuk (xlitvi02)
 * @date 2024-05-05
 */

#ifndef SIMULATIONENGINE_H
#define SIMULATIONENGINE_H

#include "QObject"
#include "QList"
#include "QTimer"
#include "vector"
#include "memory"
#include "algorithm"
#include "chrono"
#include "thread"
#include "cmath"
#include "ostream"
#include "iostream"

#include "Environment.h"
#include "Robot.h"
#include "Obstacle.h"
#include "AutonomousRobot.h"
#include "RemoteControlledRobot.h"

/**
 * @class SimulationEngine
 * @brief Manages the interactions and state of a simulated robotic environment.
 *
 * The SimulationEngine is responsible for updating the state of the environment and its entities. It controls the flow of the simulation and provides interfaces to interact with the environment.
 */

class SimulationEngine : public QObject {
    Q_OBJECT

public:
    explicit SimulationEngine(Environment* environment, QObject* parent = nullptr);
    virtual ~SimulationEngine();
    /**
     * @brief Retrieves the environment being simulated.
     * @return Pointer to the Environment object.
     */
    [[nodiscard]] Environment* getEnvironment() const { return environment; }

    void start();
    void pause();
    void resume();
    void stop();
    void update();
    void removeRobot(int id);
    void removeObstacle(int id);
    void sendCommand(const QString &command);
    void updateObstacle(int id, double size, double x, double y);
    void addObstacle(int id, const QPointF &position, double size);
    void updateRobot(int id, double speed, double orientation, double sensorSize, double x, double y);
    void addRobot(const QString &type, int id, const QPointF &position, double speed, double orientation, double sensorRange);

    Obstacle* getObstacleById(int id);
    Obstacle* findObstacleById(int id);

    /**
 * @brief Retrieves all robots in the simulation.
 * @return A vector of pointers to Robot objects.
 */
    [[nodiscard]] std::vector<Robot*> getRobots() const;
    /**
 * @brief Retrieves all obstacles in the simulation.
 * @return A vector of pointers to Obstacle objects.
 */
    [[nodiscard]] std::vector<Obstacle*> getObstacles() const;

    Robot* getRobotById(int id);
    Robot* findRobotById(int id);

signals:
    /**
 * @brief Signal to update the GUI to reflect changes in the simulation.
 */
    void updateGUI();

private:
    Environment* environment; ///< Pointer to the simulation environment.
    QTimer* timer; ///< Timer to manage simulation updates.

    bool running; ///< Flag to check if the simulation is currently running.
    double timeStep; ///< Time step for simulation updates.

    std::chrono::steady_clock::time_point startTime; ///< Start time of the simulation.
    std::chrono::steady_clock::time_point lastUpdate; ///< Time point of the last update.
    std::vector<std::unique_ptr<Robot>> robots; ///< Container for all robots in the simulation.
    std::vector<std::unique_ptr<Obstacle>> obstacles; ///< Container for all obstacles in the simulation.

};

#endif // SIMULATIONENGINE_H
