#include <QApplication>
#include "GUI.h"
#include "Environment.h"
#include "SimulationEngine.h"
#include "AutonomousRobot.h"
#include "RemoteControlledRobot.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Environment env;
    env.loadConfiguration("examples/example1.txt");
    SimulationEngine simulationEngine(&env);
    GUI gui;
    gui.setEnvironment(&env);
    gui.setSimulationEngine(&simulationEngine);
    gui.show();
    return app.exec();
}
