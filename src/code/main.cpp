#include <QApplication>
#include "gui/GuiMain.h"
#include "Environment.h"
#include "SimulationEngine.h"
#include "ConfigManager.h"
#include <QString>
#include <string>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ConfigManager::setConfigPath("examples/TEST_MAIN.txt");
    Environment env; // Assuming Environment handles configurations itself or via a method
    QString qPath = ConfigManager::getConfigPath();  // Получаем путь как QString
    std::string path = qPath.toStdString();
    env.loadConfiguration(path); // Load configuration for the simulation

    SimulationEngine *simulationEngine = new SimulationEngine(&env); // Create the simulation engine with the environment

    GuiMain gui(simulationEngine); // Pass the simulation engine to the GUI
    gui.show(); // Show the main window

    return app.exec(); // Start the Qt event loop
}