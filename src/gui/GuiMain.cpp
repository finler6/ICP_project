/**
 * @file AutonomousRobot.cpp
 * @brief Definition of the AutonomousRobot class, which extends the Robot base class with specific functionalities for autonomous navigation and obstacle detection.
 *
 * @author Pavel Stepanov (xstepa77)
 * @author Gleb Litvinchuk (xlitvi02)
 * @date 2024-05-05
 */
#include "GuiMain.h"

/**
 * @brief Constructs a new ControlPanel object with the specified parent.
 * @param parent The parent widget of the control panel.
 */
GuiMain::GuiMain(SimulationEngine* engine, QWidget* parent)
        : QMainWindow(parent), engine(engine) {
    simulationWindow = new SimulationWindow(engine, this);
    controlPanel = new ControlPanel(this);
    settingsDialog = new SettingsDialog(this);
    loadNew = new LoadEnvironment(engine->getEnvironment(), this);
    QObject::connect(loadNew, &LoadEnvironment::stopEngine, engine, &SimulationEngine::stop);
    setCentralWidget(simulationWindow);
    QDockWidget* dockWidget = new QDockWidget(this);
    dockWidget->setWidget(controlPanel);
    addDockWidget(Qt::BottomDockWidgetArea, dockWidget);

    setupConnections();
}

GuiMain::~GuiMain() {
    delete simulationWindow;
    delete controlPanel;
    delete settingsDialog;
}

/**
 * @brief Sets up the connections between the control panel buttons and the simulation window.
 */
void GuiMain::setupConnections() {
    connect(controlPanel, &ControlPanel::startSimulation, this, &GuiMain::startSimulation);
    connect(controlPanel, &ControlPanel::pauseSimulation, this, &GuiMain::pauseSimulation);
    connect(controlPanel, &ControlPanel::continueSimulation, this, &GuiMain::continueSimulation);
    connect(controlPanel, &ControlPanel::openSettings, this, &GuiMain::openSettingsDialog);
    connect(controlPanel, &ControlPanel::stopSimulation, this, &GuiMain::stopSimulation);
    connect(controlPanel, &ControlPanel::loadnewConfiguration, this, &GuiMain::loadNewConf);
}
/**
 * @brief Opens the settings dialog.
 */
void GuiMain::openSettingsDialog() {
    settingsDialog->show();
}
/**
 * @brief Starts the simulation.
 */
void GuiMain::startSimulation() {
    simulationWindow->startSimulation();
    simulationWindow->setFocus();
}
/**
 * @brief Pauses the simulation.
 */
void GuiMain::pauseSimulation() {
    simulationWindow->pauseSimulation();
}
/**
 * @brief Continues the simulation.
 */
void GuiMain::continueSimulation() {
    simulationWindow->continueSimulation();
    simulationWindow->setFocus();
}
/**
 * @brief Stops the simulation.
 */
void GuiMain::stopSimulation() {
    simulationWindow->stopSimulation();
}
/**
 * @brief Loads a new configuration.
 */
void GuiMain::loadNewConf() {
    loadNew->loadNewConfiguration();
}
/**
 * @brief Handles key press events.
 * @param event The key press event.
 */
void GuiMain::keyPressEvent(QKeyEvent *event) {
    simulationWindow->handleKeyPress(event);
}
/**
 * @brief Handles key release events.
 * @param event The key release event.
 */
void GuiMain::keyReleaseEvent(QKeyEvent *event) {
    simulationWindow->handleKeyRelease(event);
}