#include "ControlPanel.h"

ControlPanel::ControlPanel(QWidget *parent) : QWidget(parent) {
    startButton = new QPushButton(tr("Start"), this);
    pauseButton = new QPushButton(tr("Pause"), this);
    resumeButton = new QPushButton(tr("Resume"), this);
    stopButton = new QPushButton(tr("Stop"), this);
    settingsButton = new QPushButton(tr("Add Configuration"), this);
    loadButton = new QPushButton(tr("Load Configuration"), this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(startButton);
    layout->addWidget(pauseButton);
    layout->addWidget(resumeButton);
    layout->addWidget(stopButton);
    layout->addWidget(settingsButton);
    layout->addWidget(loadButton);
    setLayout(layout);

    connect(startButton, &QPushButton::clicked, this, &ControlPanel::startSimulation);
    connect(pauseButton, &QPushButton::clicked, this, &ControlPanel::pauseSimulation);
    connect(resumeButton, &QPushButton::clicked, this, &ControlPanel::continueSimulation);
    connect(stopButton, &QPushButton::clicked, this, &ControlPanel::stopSimulation);
    connect(settingsButton, &QPushButton::clicked, this, &ControlPanel::openSettings);
    connect(loadButton, &QPushButton::clicked, this, &ControlPanel::loadnewConfiguration);

}
