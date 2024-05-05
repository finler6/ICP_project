/**
 * @file AutonomousRobot.cpp
 * @brief Definition of the AutonomousRobot class, which extends the Robot base class with specific functionalities for autonomous navigation and obstacle detection.
 *
 * @author Pavel Stepanov (xstepa77)
 * @author Gleb Litvinchuk (xlitvi02)
 * @date 2024-05-05
 */
#ifndef SIMULATIONWINDOW_H
#define SIMULATIONWINDOW_H

#include "QMenu"
#include "QFile"
#include "QDebug"
#include "QAction"
#include "QWidget"
#include "QKeyEvent"
#include "QVBoxLayout"
#include "QTextStream"
#include "QGraphicsView"
#include "QGraphicsScene"
#include "QContextMenuEvent"
#include "RobotView.h"
#include "RobotDialog.h"
#include "ObstacleView.h"
#include "ObstacleDialog.h"
#include "code/ConfigManager.h"
#include "code/SimulationEngine.h"

/**
 * @class SimulationWindow
 * @brief Class representing the main window of the simulation application.
 */
class SimulationWindow : public QWidget {
Q_OBJECT
public:
    explicit SimulationWindow(SimulationEngine *engine, QWidget *parent = nullptr);
    void updateScene();
    void initializeScene();
    void startSimulation();
    void pauseSimulation();
    void continueSimulation();
    void stopSimulation();
    void handleKeyPress(QKeyEvent *event);
    void handleKeyRelease(QKeyEvent *event);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    QGraphicsView *view;
    QGraphicsScene *scene;
    QPointF clickPosition;
    SimulationEngine *engine;
    QMap<int, RobotView*> robotViews;
    QMap<int, ObstacleView*> obstacleViews;
    QString lastAddedType;
    QString lastRobotType;
    void modifyItem(QGraphicsItem* item);

    std::vector<std::unique_ptr<Robot>> robots;


private slots:
    void addRobot();
    void addObstacle();
};

#endif // SIMULATIONWINDOW_H
