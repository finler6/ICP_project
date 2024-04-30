#include "SimulationWindow.h"
#include "RobotView.h"
#include "ObstacleView.h"

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

