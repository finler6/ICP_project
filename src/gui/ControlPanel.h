/**
 * @file AutonomousRobot.cpp
 * @brief Definition of the AutonomousRobot class, which extends the Robot base class with specific functionalities for autonomous navigation and obstacle detection.
 *
 * @author Pavel Stepanov (xstepa77)
 * @author Gleb Litvinchuk (xlitvi02)
 * @date 2024-05-05
 */
#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include "QWidget"
#include "QPushButton"
#include "QVBoxLayout"

/**
 * @class ControlPanel
 * @brief Represents a control panel for the simulation interface.
 *
 * This class provides a control panel with buttons for starting, pausing, resuming, and stopping the simulation,
 * as well as for opening the settings dialog and loading a new configuration.
 */
class ControlPanel : public QWidget {
    Q_OBJECT

public:
    explicit ControlPanel(QWidget *parent = nullptr);

signals:
    void startSimulation();
    void pauseSimulation();
    void continueSimulation();
    void stopSimulation();
    void openSettings();       
    void loadnewConfiguration();   

private:
    QPushButton *startButton;
    QPushButton *pauseButton;
    QPushButton *resumeButton;
    QPushButton *stopButton;
    QPushButton *settingsButton;
    QPushButton *loadButton;
};

#endif 

