// MapEditor.cpp
#include "MapEditor.h"
#include <QTextStream>
#include <QFile>

MapEditor::MapEditor(QWidget *parent) : QGraphicsView(parent) {
    setScene(new QGraphicsScene(this));
    scene()->setSceneRect(0, 0, 800, 600);
}

void MapEditor::contextMenuEvent(QContextMenuEvent *event) {
    clickPosition = mapToScene(event->pos());
    QMenu menu(this);
    menu.addAction("Add Robot", this, &MapEditor::addRobot);
    menu.addAction("Add Obstacle", this, &MapEditor::addObstacle);
    menu.exec(event->globalPos());
}
void MapEditor::addRobot() {
    RobotDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        lastRobotType = dialog.getType();
        lastRobotId = dialog.getId();
        lastRobotPosition = clickPosition;
        lastRobotSpeed = dialog.getSpeed();
        lastRobotOrientation = dialog.getOrientation();
        lastRobotSensorSize = dialog.getSensorSize();

        RobotView *robotView = new RobotView();
        robotView->setPosition(lastRobotPosition);
        robotView->setOrientation(lastRobotOrientation);
        scene()->addItem(robotView);
        saveConfiguration();
    }
}

void MapEditor::addObstacle() {
    ObstacleDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        lastObstacleId = dialog.getId();
        lastObstaclePosition = clickPosition;
        lastObstacleSize = dialog.getSize();

        QRectF bounds(lastObstaclePosition.x() - lastObstacleSize/2, lastObstaclePosition.y() - lastObstacleSize/2, lastObstacleSize, lastObstacleSize);
        ObstacleView *obstacleView = new ObstacleView(bounds);
        scene()->addItem(obstacleView);
        saveConfiguration();
    }
}


void MapEditor::saveConfiguration() {
    QFile file(ConfigManager::getConfigPath());
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        return;

    QTextStream out(&file);
    // Запись данных робота
    out << "Robot " << lastRobotType << " " << lastRobotId << " "
        << lastRobotPosition.x() << " " << lastRobotPosition.y() << " "
        << lastRobotSpeed << " " << lastRobotOrientation << " "
        << lastRobotSensorSize << "\n";

    // Запись данных препятствия
    out << "Obstacle " << lastObstacleId << " "
        << lastObstaclePosition.x() << " " << lastObstaclePosition.y() << " "
        << lastObstacleSize << "\n";

    file.close();
}