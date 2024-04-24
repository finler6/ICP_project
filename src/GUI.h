#pragma once
#include <QPushButton>
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "SimulationEngine.h"
#include "Environment.h"
#include <QTimer>
#include <QWidget>


class GUI : public QMainWindow {
    Q_OBJECT

public:
    explicit GUI(QWidget *parent = nullptr);
    ~GUI();
    void setSimulationEngine(SimulationEngine* engine);
    void updateDisplay(); // Обновление отображения симуляции
    void setEnvironment(Environment* env); // Установка ссылки на Environment
    void setupUpdateTimer();

private:
    QPushButton* startButton;
    QPushButton* stopButton;
    QGraphicsView* view;
    QGraphicsScene* scene;
    QTimer *updateTimer;
    SimulationEngine* simulationEngine;
    Environment* environment;

    void setupUI();
    void connectSignals();
    
protected:
    void paintEvent(QPaintEvent *event) override; // Переопределение метода paintEvent

private slots:
    void onStartClicked();
    void onStopClicked();
};
