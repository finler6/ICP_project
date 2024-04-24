#pragma once
#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "SimulationEngine.h"

class GUI : public QMainWindow {
    Q_OBJECT

public:
    explicit GUI(QWidget *parent = nullptr);
    ~GUI();

private:
    QPushButton* startButton;
    QPushButton* stopButton;
    QGraphicsView* view;
    QGraphicsScene* scene;
    SimulationEngine* simulationEngine;

    void setupUI();
    void connectSignals();

private slots:
    void onStartClicked();
    void onStopClicked();
};
