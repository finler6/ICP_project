#include "GUI.h"
#include "Environment.h"
#include "SimulationEngine.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QKeyEvent>



GUI::GUI(QWidget *parent) : QMainWindow(parent), updateTimer(new QTimer(this)) {
    setFocusPolicy(Qt::StrongFocus);
    setupUI();
    setupUpdateTimer();
    connectSignals();
    initializeScene();
}


GUI::~GUI() {
    delete simulationEngine;
}
void GUI::setupUpdateTimer() {
    connect(updateTimer, &QTimer::timeout, this, &GUI::updateDisplay);
    updateTimer->start(16);  // Запускаем таймер на 16 мс для обновления при 60 FPS
}

void GUI::setSimulationEngine(SimulationEngine* engine) {
    if (engine) {
        this->simulationEngine = engine;
        connect(simulationEngine, &SimulationEngine::updateGUI, this, &GUI::redraw, Qt::QueuedConnection);
    } else {
        qDebug() << "Provided simulation engine is null!";
    }
}


void GUI::setupUI() {
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, centralWidget);
    layout->addWidget(view);

    startButton = new QPushButton("Start", centralWidget);
    stopButton = new QPushButton("Stop", centralWidget);
    layout->addWidget(startButton);
    layout->addWidget(stopButton);

    centralWidget->setLayout(layout);
    resize(800, 600);
    setWindowTitle("Robot Simulation");

    // Добавление объектов на сцену
    initializeScene(); // Новый метод для инициализации сцены
}

void GUI::initializeScene() {
    if (!scene) {
        qDebug() << "Scene not initialized!";
        return;  // Выход, если сцена не инициализирована
    }

    if (!environment) {
        qDebug() << "Environment not set!";
        return;  // Выход, если environment не установлен
    }

    scene->clear(); // Очистка сцены перед добавлением элементов

    for (const auto& obstacle : environment->getObstacles()) {
        if (!scene->addRect(obstacle.getPosition().first, obstacle.getPosition().second,
                            obstacle.getSize(), obstacle.getSize(), QPen(Qt::NoPen), QBrush(Qt::black))) {
            qDebug() << "Failed to add obstacle to scene";
        }
    }
    for (const auto& robot : environment->getRobots()) {
        QPointF pos(robot->getPosition().first, robot->getPosition().second);
        double radius = robot->getSize() / 2;  // Предполагаем, что size — это диаметр
        scene->addEllipse(pos.x() - radius, pos.y() - radius, robot->getSize(), robot->getSize(), QPen(Qt::NoPen), QBrush(Qt::red));
    }
}

void GUI::connectSignals() {
    connect(startButton, &QPushButton::clicked, this, &GUI::onStartClicked);
    connect(stopButton, &QPushButton::clicked, this, &GUI::onStopClicked);
}

void GUI::setEnvironment(Environment* env) {
    this->environment = env; // Сохранение ссылки на окружающую среду
}


void GUI::onStartClicked() {
    if (simulationEngine) { // Проверка, что simulationEngine инициализирован
        simulationEngine->start();
    } else {
        qDebug() << "Simulation engine is not initialized!";
    }
}

void GUI::onStopClicked() {
    if (simulationEngine) {
        simulationEngine->stop();
    }
}

void GUI::updateDisplay() {
    scene->clear();
    initializeScene(); // Обновляем сцену с текущими данными
}

void GUI::redraw() {
    updateDisplay(); // Перенаправляем вызовы redraw на updateDisplay
}

void GUI::keyPressEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) {
        event->ignore();
        return; // Игнорируем события автоповтора
    }

    switch (event->key()) {
        case Qt::Key_Up:
            remoteControlledRobot->setMoveForward(true);
            break;
        case Qt::Key_Down:
            remoteControlledRobot->setMoveForward(false);
            break;
        case Qt::Key_Left:
            remoteControlledRobot->setRotateDirection(-10); // Повернуть налево на 10 градусов
            break;
        case Qt::Key_Right:
            remoteControlledRobot->setRotateDirection(10); // Повернуть направо на 10 градусов
            break;
        default:
            QMainWindow::keyPressEvent(event);
    }
}