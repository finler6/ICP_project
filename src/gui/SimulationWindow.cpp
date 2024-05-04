#include <QFile>
#include <QKeyEvent>
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
    setFocusPolicy(Qt::StrongFocus);
    //setFocus();
}

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

void SimulationWindow::keyPressEvent(QKeyEvent *event) {
    this->setFocus();  // Устанавливаем фокус на SimulationWindow
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
            QWidget::keyPressEvent(event); // Передаем обработку дальше, если клавиша не обработана
    }
}

void SimulationWindow::keyReleaseEvent(QKeyEvent *event) {
    if (event->isAutoRepeat())  // Игнорируем события автоповтора
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
            QWidget::keyReleaseEvent(event); // Передаем обработку дальше, если клавиша не обработана
    }
}

void SimulationWindow::addRobot() {
    RobotDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString type = dialog.getType();
        int id = dialog.getId();
        QPointF position = clickPosition;
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


void SimulationWindow::addObstacle() {
    ObstacleDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        int id = dialog.getId();
        QPointF position = clickPosition;
        double size = dialog.getSize();

        engine->addObstacle(id, position, size);

        QGraphicsRectItem* obstacleItem = new QGraphicsRectItem(
            position.x() - size / 2, position.y() - size / 2, size, size
        );
        obstacleItem->setBrush(Qt::gray);  
        scene->addItem(obstacleItem);
    }
}

void SimulationWindow::modifyItem(QGraphicsItem* item) {
    if (auto robotView = dynamic_cast<RobotView*>(item)) {
        RobotDialog dialog(this);
        dialog.setInitialValues(robotView->getSpeed(), robotView->getOrientation(), robotView->getSensorRange());
        if (dialog.exec() == QDialog::Accepted) {
            engine->updateRobot(robotView->getId(), dialog.getSpeed(), dialog.getOrientation(), dialog.getSensorSize());
            robotView->updateRobotView();
        }
    } else if (auto obstacleView = dynamic_cast<ObstacleView*>(item)) {
        ObstacleDialog dialog(this);
        dialog.setInitialSize(obstacleView->getSize());
        if (dialog.exec() == QDialog::Accepted) {
            engine->updateObstacle(obstacleView->getId(), dialog.getSize());
            obstacleView->updateObstacleView();
        }
    }
    updateScene();
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
    updateScene();
}

void SimulationWindow::initializeScene() {
    scene->clear();
    robotViews.clear();
    obstacleViews.clear();
    auto robots = engine->getRobots();
    for (const auto& robot : robots) {
        RobotView* robotView = new RobotView(engine, robot->getID(), nullptr);
        qDebug() << "Creating RobotView with ID:" << robot->getID();
        robotView->setPos(QPointF(robot->getPosition().first, robot->getPosition().second));
        robotView->setRotation(robot->getOrientation());
        robotView->setSensorRange(robot->getSensorRange());
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
    //setfocus
}



void SimulationWindow::startSimulation() {
    engine->start();
    this->setFocus();  // Возвращаем фокус на виджет SimulationWindow
}

void SimulationWindow::pauseSimulation() {
    engine->pause();
}

void SimulationWindow::continueSimulation() {
    engine->resume();
    this->setFocus();  // Возвращаем фокус на виджет SimulationWindow
}

void SimulationWindow::stopSimulation() {
    engine->stop();
}

