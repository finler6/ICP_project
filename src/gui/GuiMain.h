/**
 * @file AutonomousRobot.cpp
 * @brief Definition of the AutonomousRobot class, which extends the Robot base class with specific functionalities for autonomous navigation and obstacle detection.
 *
 * @author Pavel Stepanov (xstepa77)
 * @author Gleb Litvinchuk (xlitvi02)
 * @date 2024-05-05
 */
#ifndef GUIMAIN_H
#define GUIMAIN_H

#include "QMainWindow"
#include "QDockWidget"
#include "ControlPanel.h"
#include "SettingsDialog.h"
#include "LoadEnvironment.h"
#include "SimulationWindow.h"
#include "code/SimulationEngine.h"

/**
 * @class GuiMain
 * @brief Represents the main window of the simulation interface.
 *
 * This class provides the main window of the simulation interface, which contains the simulation window, control panel,
 * and settings dialog.
 */
class GuiMain : public QMainWindow {
Q_OBJECT

public:
    explicit GuiMain(SimulationEngine* engine, QWidget *parent = nullptr);
    ~GuiMain();
    void loadNewConf();

private:
    void setupConnections();
    SimulationWindow *simulationWindow;
    ControlPanel *controlPanel;
    SettingsDialog *settingsDialog;
    SimulationEngine* engine;
    LoadEnvironment* loadNew;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;


public slots:
    void openSettingsDialog();

private slots:
    void startSimulation();
    void pauseSimulation();
    void continueSimulation();
    void stopSimulation();
};

#endif 
