#include <QFile>
#include "SimulationWindow.h"

SimulationWindow::SimulationWindow(SimulationEngine *engine, QWidget *parent)
    : QWidget(parent), engine(engine) {
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    view->setSceneRect(0, 0, 800, 600);
    view->setFixedSize(820, 620);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(view);
    setLayout(layout);

    initializeScene();
    connect(engine, &SimulationEngine::updateGUI, this, &SimulationWindow::updateScene);
}

void SimulationWindow::contextMenuEvent(QContextMenuEvent *event) {
    clickPosition = view->mapToScene(event->pos());
    QMenu menu;
    menu.addAction("Add Robot", this, &SimulationWindow::addRobot);
    menu.addAction("Add Obstacle", this, &SimulationWindow::addObstacle);
    menu.exec(event->globalPos());
}

void SimulationWindow::addRobot() {
    RobotDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        // Сбор данных из диалога
        QString type = dialog.getType();
        int id = dialog.getId();
        QPointF position = clickPosition;
        double speed = dialog.getSpeed();
        double orientation = dialog.getOrientation();
        double sensorSize = dialog.getSensorSize();


        // Передача данных в SimulationEngine, который перенаправляет их в Environment
        engine->addRobot(type, id, position, speed, orientation, sensorSize);

        // Отображение робота на сцене (опционально, зависит от архитектуры приложения)
        QGraphicsEllipseItem* robotItem = new QGraphicsEllipseItem(
            position.x() - 10, position.y() - 10, 20, 20
        );
        robotItem->setBrush(Qt::blue);  // Примерная визуализация
        scene->addItem(robotItem);
    }
}


void SimulationWindow::addObstacle() {
    ObstacleDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        int id = dialog.getId();
        QPointF position = clickPosition;
        double size = dialog.getSize();

        // Передача данных для создания и добавления препятствия в модель
        engine->addObstacle(id, position, size);

        // Опционально: отображение препятствия на сцене
        QGraphicsRectItem* obstacleItem = new QGraphicsRectItem(
            position.x() - size / 2, position.y() - size / 2, size, size
        );
        obstacleItem->setBrush(Qt::gray);  // Визуальное представление
        scene->addItem(obstacleItem);
    }
}




void SimulationWindow::saveConfiguration() {
    QFile file(ConfigManager::getConfigPath());
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Cannot open file for appending: " << file.errorString();
        return;
    }

    QTextStream out(&file);
    if (lastAddedType == "Robot") {
        out << "Robot " << lastRobotType << " " << lastAddedId << " "
            << lastAddedX << " " << lastAddedY << " "
            << lastAddedParam1 << " " << lastAddedParam2 << " " << lastAddedParam3 << "\n";
    } else if (lastAddedType == "Obstacle") {
        out << "Obstacle " << lastAddedId << " " << lastAddedX << " " << lastAddedY << " " << lastAddedParam1 << "\n";
    }

    file.close();
}



void SimulationWindow::onGuiUpdate() {
    updateScene();  // Вызываем метод обновления сцены
}

void SimulationWindow::initializeScene() {
    scene->clear();
    robotViews.clear();
    obstacleViews.clear();

    auto robots = engine->getRobots();
    for (const auto& robot : robots) {
        RobotView* robotView = new RobotView();
        robotView->setPosition(QPointF(robot->getPosition().first, robot->getPosition().second));
        robotView->setOrientation(robot->getOrientation());
        robotView->setSensorRange(robot->getSensorRange());  // Передача диапазона сенсора
        scene->addItem(robotView);
        robotViews.insert(robot->getID(), robotView);
    }

    auto obstacles = engine->getObstacles();
    for (const auto& obstacle : obstacles) {
        ObstacleView *obstacleView = new ObstacleView(obstacle->getBounds());
        scene->addItem(obstacleView);
        obstacleViews.insert(obstacle->getId(), obstacleView);
    }
}


void SimulationWindow::updateScene() {
    scene->clear();  // Полностью очищаем сцену
    robotViews.clear();  // Очищаем текущие представления роботов
    obstacleViews.clear();  // Очищаем текущие представления препятствий

    // Пересоздаём представления для всех роботов
    auto robots = engine->getRobots();
    for (const auto& robot : robots) {
        RobotView* robotView = new RobotView();
        robotView->setPosition(QPointF(robot->getPosition().first, robot->getPosition().second));
        robotView->setOrientation(robot->getOrientation());
        scene->addItem(robotView);
        robotViews.insert(robot->getID(), robotView);
    }

    // Пересоздаём представления для всех препятствий
    auto obstacles = engine->getObstacles();
    for (const auto& obstacle : obstacles) {
        ObstacleView* obstacleView = new ObstacleView(obstacle->getBounds());
        scene->addItem(obstacleView);
        obstacleViews.insert(obstacle->getId(), obstacleView);
    }

    scene->update();  // Обновляем сцену для отображения изменений
}

void SimulationWindow::startSimulation() {
    engine->start();
}

void SimulationWindow::pauseSimulation() {
    engine->pause();
}

void SimulationWindow::continueSimulation() {
    engine->resume();
}

void SimulationWindow::stopSimulation() {
    engine->stop();
}

