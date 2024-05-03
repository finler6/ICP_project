#include "GuiMain.h"
#include <QDockWidget>

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

void GuiMain::setupConnections() {
    connect(controlPanel, &ControlPanel::startSimulation, this, &GuiMain::startSimulation);
    connect(controlPanel, &ControlPanel::pauseSimulation, this, &GuiMain::pauseSimulation);
    connect(controlPanel, &ControlPanel::continueSimulation, this, &GuiMain::continueSimulation);
    connect(controlPanel, &ControlPanel::openSettings, this, &GuiMain::openSettingsDialog);
    connect(controlPanel, &ControlPanel::stopSimulation, this, &GuiMain::stopSimulation);
    connect(controlPanel, &ControlPanel::loadnewConfiguration, this, &GuiMain::loadNewConf);
}

void GuiMain::openSettingsDialog() {
    settingsDialog->show();  
}

void GuiMain::startSimulation() {
    simulationWindow->startSimulation();
}

void GuiMain::pauseSimulation() {
    simulationWindow->pauseSimulation();
}

void GuiMain::continueSimulation() {
    simulationWindow->continueSimulation();
}

void GuiMain::stopSimulation() {
    simulationWindow->stopSimulation();
}

void GuiMain::loadNewConf() {
    loadNew->loadNewConfiguration();
}
