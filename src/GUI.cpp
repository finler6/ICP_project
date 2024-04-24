#include "GUI.h"
#include "Environment.h"
#include "SimulationEngine.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>


GUI::GUI(QWidget *parent) : QMainWindow(parent), updateTimer(new QTimer(this)) {
    setupUI();
    setupUpdateTimer();
}

GUI::~GUI() {
    delete simulationEngine;
}
void GUI::setupUpdateTimer() {
    connect(updateTimer, &QTimer::timeout, this, &GUI::updateDisplay);
    updateTimer->start(16);  // Запускаем таймер на 16 мс для обновления при 60 FPS
}

void GUI::setSimulationEngine(SimulationEngine* engine) {
    this->simulationEngine = engine;
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
}

void GUI::connectSignals() {
    connect(startButton, &QPushButton::clicked, this, &GUI::onStartClicked);
    connect(stopButton, &QPushButton::clicked, this, &GUI::onStopClicked);
}

void GUI::setEnvironment(Environment* env) {
    this->environment = env; // Сохранение ссылки на окружающую среду
}

void GUI::onStartClicked() {
    simulationEngine->start();
}

void GUI::onStopClicked() {
    simulationEngine->stop();
}

void GUI::updateDisplay() {
    update();
}

void GUI::paintEvent(QPaintEvent *event) {
    (void)event;
    if (!environment) {
        qDebug() << "Environment not set!";
        return;
    }
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Пример рисования препятствия
    for (const auto& obstacle : environment->getObstacles()) {
        painter.setBrush(Qt::black);
        painter.drawRect(obstacle.getPosition().first, obstacle.getPosition().second, obstacle.getSize(), obstacle.getSize());
    }

    // Пример рисования робота
    for (const auto& robot : environment->getRobots()) {
        painter.setBrush(Qt::red);
        painter.drawEllipse(QPointF(robot->getPosition().first, robot->getPosition().second), qreal(robot->getSize()), qreal(robot->getSize()));
    }
}
