// MapEditor.h
#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include "RobotDialog.h"
#include "ObstacleDialog.h"
#include "RobotView.h"
#include "ObstacleView.h"
#include "code/ConfigManager.h"

class MapEditor : public QGraphicsView {
    Q_OBJECT

public:
    explicit MapEditor(QWidget *parent = nullptr);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private slots:
    void addRobot();
    void addObstacle();

private:
    QPointF clickPosition;
    void saveConfiguration();

    // Данные последнего созданного робота
    QString lastRobotType;
    int lastRobotId;
    QPointF lastRobotPosition;
    double lastRobotSpeed;
    double lastRobotOrientation;
    double lastRobotSensorSize;

    // Данные последнего созданного препятствия
    int lastObstacleId;
    QPointF lastObstaclePosition;
    double lastObstacleSize;
};

#endif // MAPEDITOR_H