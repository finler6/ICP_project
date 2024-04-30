#ifndef GUIMAIN_H
#define GUIMAIN_H

#include <QMainWindow>
#include "SimulationWindow.h"
#include "ControlPanel.h"
#include "SettingsDialog.h"
#include "code/SimulationEngine.h"
#include <QDockWidget>
#include "LoadEnvironment.h"
#include "MapEditor.h"


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
    MapEditor *mapEditor;


public slots:
    void openSettingsDialog();  // Slot to handle settings dialog opening

private slots:
    void startSimulation();
    void pauseSimulation();
    void continueSimulation();
    void stopSimulation();
   // Slot to handle loading new configuration
};

#endif // GUIMAIN_H
