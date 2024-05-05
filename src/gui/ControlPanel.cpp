/**
 * @file AutonomousRobot.cpp
 * @brief Definition of the AutonomousRobot class, which extends the Robot base class with specific functionalities for autonomous navigation and obstacle detection.
 *
 * @author Pavel Stepanov (xstepa77)
 * @author Gleb Litvinchuk (xlitvi02)
 * @date 2024-05-05
 */
#include "ControlPanel.h"

/**
 * @brief Constructs a new ControlPanel object with the specified parent.
 * @param parent The parent widget of the control panel.
 */
ControlPanel::ControlPanel(QWidget *parent) : QWidget(parent) {
    // Create buttons for the control panel
    startButton = new QPushButton(tr("Start"), this);
    pauseButton = new QPushButton(tr("Pause"), this);
    resumeButton = new QPushButton(tr("Resume"), this);
    stopButton = new QPushButton(tr("Stop"), this);
    settingsButton = new QPushButton(tr("Add Configuration"), this);
    loadButton = new QPushButton(tr("Load Configuration"), this);

    // Create a vertical layout for the control panel
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(startButton);
    layout->addWidget(pauseButton);
    layout->addWidget(resumeButton);
    layout->addWidget(stopButton);
    layout->addWidget(settingsButton);
    layout->addWidget(loadButton);
    setLayout(layout);

    // Connect signals and slots for the control panel buttons
    connect(startButton, &QPushButton::clicked, this, &ControlPanel::startSimulation);
    connect(pauseButton, &QPushButton::clicked, this, &ControlPanel::pauseSimulation);
    connect(resumeButton, &QPushButton::clicked, this, &ControlPanel::continueSimulation);
    connect(stopButton, &QPushButton::clicked, this, &ControlPanel::stopSimulation);
    connect(settingsButton, &QPushButton::clicked, this, &ControlPanel::openSettings);
    connect(loadButton, &QPushButton::clicked, this, &ControlPanel::loadnewConfiguration);

}
