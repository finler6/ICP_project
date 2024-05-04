#ifndef SIMULATIONWINDOW_H
#define SIMULATIONWINDOW_H

#include <QDebug>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QContextMenuEvent>
#include <QTextStream>
#include <QMenu>
#include <QAction>
#include "code/SimulationEngine.h"
#include "code/ConfigManager.h"
#include "RobotView.h"
#include "ObstacleView.h"
#include "RobotDialog.h"
#include "ObstacleDialog.h"

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

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;  // Обработчик событий клавиатуры
    void keyReleaseEvent(QKeyEvent *event) override;  // Обработчик событий клавиатуры

private:
    QGraphicsView *view;
    QGraphicsScene *scene;
    QPointF clickPosition;
    SimulationEngine *engine;
    QMap<int, RobotView*> robotViews;
    QMap<int, ObstacleView*> obstacleViews;
    QString lastAddedType; 
    QString lastRobotType; 
    int lastAddedId;
    double lastAddedX, lastAddedY;
    double lastAddedParam1, lastAddedParam2, lastAddedParam3;
    void modifyItem(QGraphicsItem* item);

    std::vector<std::unique_ptr<Robot>> robots;


private slots:
    void onGuiUpdate();
    void addRobot();
    void addObstacle();
    void saveConfiguration();
};

#endif // SIMULATIONWINDOW_H
