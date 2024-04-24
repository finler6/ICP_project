#include "GUI.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

GUI::GUI(QWidget *parent) : QMainWindow(parent), simulationEngine(new SimulationEngine(/* Pass the environment here */)) {
    setupUI();
    connectSignals();
}

GUI::~GUI() {
    delete simulationEngine;
}

void GUI::setupUI() {
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, centralWidget);
    layout->addWidget(view);

    startButton = new QPushButton("Start", centralWidget);
    stopButton = new QPushButton("Stop", centralWidget);
    layout->addWidget(startButton);
    layout->addWidget(stopButton);

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    resize(800, 600);
    setWindowTitle("Robot Simulation");
}

void GUI::connectSignals() {
    connect(startButton, &QPushButton::clicked, this, &GUI::onStartClicked);
    connect(stopButton, &QPushButton::clicked, this, &GUI::onStopClicked);
}

void GUI::onStartClicked() {
    simulationEngine->start();
}

void GUI::onStopClicked() {
    simulationEngine->stop();
}

