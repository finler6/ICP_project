/**
 * @file AutonomousRobot.cpp
 * @brief Definition of the AutonomousRobot class, which extends the Robot base class with specific functionalities for autonomous navigation and obstacle detection.
 *
 * @author Pavel Stepanov (xstepa77)
 * @author Gleb Litvinchuk (xlitvi02)
 * @date 2024-05-05
 */
#include "SimulationWindow.h"

/**
 * @brief Constructor for the SimulationWindow class.
 * @param engine Pointer to the SimulationEngine object.
 * @param parent Pointer to the parent QWidget object.
 */
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

/**
 * @brief Context menu event handler for the SimulationWindow class.
 */
void SimulationWindow::contextMenuEvent(QContextMenuEvent *event) {
    QPointF scenePoint = view->mapToScene(event->pos());
    QGraphicsItem* item = scene->itemAt(scenePoint, QTransform());
    clickPosition = view->mapToScene(event->pos());

    QMenu menu;

    if (item) {
        emit pauseSimulation();
        QAction* removeAction = menu.addAction("Delete Object");
        QAction* modifyAction = menu.addAction("Edit Object");
        connect(removeAction, &QAction::triggered, [this, item]() {
            std::cout << "Attempting to remove an item from the scene." << std::endl;
            if (item && scene->items().contains(item)) {
                std::cout << "Item is valid and exists in the scene." << std::endl;
                if (auto robotView = dynamic_cast<RobotView*>(item)) {
                    int robotId = robotView->getId();
                    std::cout << "Request to remove robot with ID: " << robotId << std::endl;
                    engine->removeRobot(robotId);
                    emit continueSimulation();
                } else if (auto obstacleView = dynamic_cast<ObstacleView*>(item)) {
                    int obstacleId = obstacleView->getId();
                    engine->removeObstacle(obstacleId);
                    emit continueSimulation();
                } else {
                    emit continueSimulation();
                }
                scene->removeItem(item);
                delete item;
            } else {
                std::cout << "Item is invalid or does not exist in the scene." << std::endl;
            }
        });
        connect(modifyAction, &QAction::triggered, [this, item]() { modifyItem(item); });

    } else {
        QAction* addRobotAction = menu.addAction("Add Robot");
        QAction* addObstacleAction = menu.addAction("Add Obstacle");
        connect(addRobotAction, &QAction::triggered, this, &SimulationWindow::addRobot);
        connect(addObstacleAction, &QAction::triggered, this, &SimulationWindow::addObstacle);
    }
    menu.exec(event->globalPos());
}

/**
 * @brief Key press event handler for the SimulationWindow class.
 */
void SimulationWindow::handleKeyPress(QKeyEvent *event) {
    if (event->isAutoRepeat())  // Игнорируем события автоповтора
        return;

    switch (event->key()) {
        case Qt::Key_Up:
            engine->sendCommand("start_move_forward");
            break;
        case Qt::Key_Down:
            engine->sendCommand("start_move_backward");
            break;
        case Qt::Key_Left:
            engine->sendCommand("start_turn_left");
            break;
        case Qt::Key_Right:
            engine->sendCommand("start_turn_right");
            break;
        default:
            QWidget::keyPressEvent(event);
    }
}

/**
 * @brief Key release event handler for the SimulationWindow class.
 */
void SimulationWindow::handleKeyRelease(QKeyEvent *event) {
    if (event->isAutoRepeat())
        return;

    switch (event->key()) {
        case Qt::Key_Up:
            engine->sendCommand("stop_move_forward");
            break;
        case Qt::Key_Down:
            engine->sendCommand("stop_move_backward");
            break;
        case Qt::Key_Left:
            engine->sendCommand("stop_turn_left");
            break;
        case Qt::Key_Right:
            engine->sendCommand("stop_turn_right");
            break;
        default:
            QWidget::keyReleaseEvent(event);
    }
}

/**
 * @brief Add a robot to the scene.
 */
void SimulationWindow::addRobot() {
    RobotDialog dialog(clickPosition, this);
    if (dialog.exec() == QDialog::Accepted) {
        QString type = dialog.getType();
        int id = dialog.getId();
        QPointF position = dialog.getPosition();
        double speed = dialog.getSpeed();
        double orientation = dialog.getOrientation();
        double sensorSize = dialog.getSensorSize();
        engine->addRobot(type, id, position, speed, orientation, sensorSize);
        QGraphicsEllipseItem* robotItem = new QGraphicsEllipseItem(
                position.x() - 10, position.y() - 10, 20, 20
        );
        robotItem->setBrush(Qt::blue);
        scene->addItem(robotItem);
    }
}

/**
 * @brief Add an obstacle to the scene.
 */
void SimulationWindow::addObstacle() {
    ObstacleDialog dialog(clickPosition, this);
    if (dialog.exec() == QDialog::Accepted) {
        int id = dialog.getId();
        QPointF position = dialog.getPosition();
        double size = dialog.getSize();

        engine->addObstacle(id, position, size);

        QGraphicsRectItem* obstacleItem = new QGraphicsRectItem(
                position.x() - size / 2, position.y() - size / 2, size, size
        );
        obstacleItem->setBrush(Qt::gray);
        scene->addItem(obstacleItem);
    }
}

/**
 * @brief Modify an item in the scene.
 */
void SimulationWindow::modifyItem(QGraphicsItem* item) {
    if (auto robotView = dynamic_cast<RobotView*>(item)) {
        RobotDialog dialog(clickPosition, this);
        dialog.setInitialValues(robotView->getId(), robotView->getSpeed(), robotView->getOrientation(), robotView->getSensorRange(), robotView->getPosition());
        if (dialog.exec() == QDialog::Accepted) {
            engine->updateRobot(robotView->getId(), dialog.getSpeed(), dialog.getOrientation(), dialog.getSensorSize(), dialog.getPosition().x(), dialog.getPosition().y());
        }
    } else if (auto obstacleView = dynamic_cast<ObstacleView*>(item)) {
        ObstacleDialog dialog(clickPosition, this);
        dialog.setInitialSize(obstacleView->getId(), obstacleView->getSize(), obstacleView->getPosition());
        if (dialog.exec() == QDialog::Accepted) {
            engine->updateObstacle(obstacleView->getId(), dialog.getSize(), dialog.getPosition().x(), dialog.getPosition().y());
        }
    }
    updateScene();
}

/**
 * @brief Initialize the scene with robots and obstacles.
 * @details This method is called when the simulation window is created.
 */
void SimulationWindow::initializeScene() {
    scene->clear();
    robotViews.clear();
    obstacleViews.clear();
    auto robots = engine->getRobots();
    for (const auto& robot : robots) {
        RobotView* robotView = new RobotView(engine, robot->getID(), nullptr);
        robotView->setPos(QPointF(robot->getPosition().first, robot->getPosition().second));
        robotView->setRotation(robot->getOrientation());
        robotView->setSensorRange(robot->getSensorRange());
        robotView->setRobot(robot);
        scene->addItem(robotView);
        robotViews.insert(robot->getID(), robotView);
    }

    auto obstacles = engine->getObstacles();
    for (const auto& obstacle : obstacles) {
        ObstacleView* obstacleView = new ObstacleView(engine, obstacle->getId(), obstacle->getBounds(), nullptr);
        scene->addItem(obstacleView);
        obstacleViews.insert(obstacle->getId(), obstacleView);
    }
}

/**
 * @brief Update the scene with the current state of the simulation.
 * @details This method is called when the simulation engine emits the updateGUI signal.
 */
void SimulationWindow::updateScene() {
    scene->clear();
    robotViews.clear();
    obstacleViews.clear();

    auto robots = engine->getRobots();
    for (const auto& robot : robots) {
        RobotView* robotView = new RobotView(engine, robot->getID(), nullptr);
        robotView->setPosition(QPointF(robot->getPosition().first, robot->getPosition().second));
        robotView->setOrientation(robot->getOrientation());
        robotView->setSensorRange(robot->getSensorRange());
        robotView->setRobot(robot);
        scene->addItem(robotView);
        robotViews.insert(robot->getID(), robotView);
    }

    auto obstacles = engine->getObstacles();
    for (const auto& obstacle : obstacles) {
        ObstacleView* obstacleView = new ObstacleView(engine, obstacle->getId(), obstacle->getBounds(), nullptr);
        scene->addItem(obstacleView);
        obstacleViews.insert(obstacle->getId(), obstacleView);
    }
    scene->update();
}

/**
 * @brief Start the simulation.
 */
void SimulationWindow::startSimulation() {
    engine->start();
    setFocus();
}

/**
 * @brief Pause the simulation.
 */
void SimulationWindow::pauseSimulation() {
    engine->pause();
}

/**
 * @brief Continue the simulation.
 */
void SimulationWindow::continueSimulation() {
    engine->resume();
    setFocus();
}

/**
 * @brief Stop the simulation.
 */
void SimulationWindow::stopSimulation() {
    engine->stop();
}

