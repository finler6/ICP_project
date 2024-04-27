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
    connect(engine, &SimulationEngine::updateGUI, this, &SimulationWindow::onGuiUpdate);
}

void SimulationWindow::onGuiUpdate() {
    updateScene();  // Вызываем метод обновления сцены
}

void SimulationWindow::initializeScene() {
    auto robots = engine->getRobots(); // Получаем текущее состояние роботов
    auto obstacles = engine->getObstacles(); // Получаем текущее состояние препятствий
    for (const auto& robot : robots) {
        RobotView* robotView = new RobotView();
        robotView->setPosition(QPointF(robot->getPosition().first, robot->getPosition().second));
        robotView->setOrientation(robot->getOrientation());
        scene->addItem(robotView);
        robotViews.insert(robot->getID(), robotView);  // Связываем RobotView с ID робота
    }

    for (const auto& obstacle : obstacles) {
        ObstacleView *obstacleView = new ObstacleView(obstacle->getBounds());
        scene->addItem(obstacleView);
    }
}

void SimulationWindow::updateScene() {
    auto robots = engine->getRobots();

    for (const auto& robot : robots) {
        RobotView* robotView = robotViews.value(robot->getID());  // Используем value(), чтобы избежать добавления null элементов
        if (robotView) {
        robotView->setPosition(QPointF(robot->getPosition().first, robot->getPosition().second));
        robotView->setOrientation(robot->getOrientation());
            robotView->update();  // Обновляем виджет, если это необходимо
        }
    }

    scene->update();  // Обновляем всю сцену
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

