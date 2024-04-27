#ifndef SIMULATIONWINDOW_H
#define SIMULATIONWINDOW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include "SimulationEngine.h"
#include "RobotView.h"
#include "ObstacleView.h"

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

private:
    QGraphicsView *view;
    QGraphicsScene *scene;
    SimulationEngine *engine;
    QMap<int, RobotView*> robotViews;
    QMap<int, ObstacleView*> obstacleViews;

private slots:
    void onGuiUpdate();
};

#endif // SIMULATIONWINDOW_H
