#include <QApplication>
#include "gui/GuiMain.h"
#include "Environment.h"
#include "SimulationEngine.h"
#include "ConfigManager.h"
#include <QString>
#include <string>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ConfigManager::setConfigPath("examples/example1.txt");
    Environment env; 
    QString qPath = ConfigManager::getConfigPath();  
    std::string path = qPath.toStdString();
    env.loadConfiguration(path); 

    SimulationEngine *simulationEngine = new SimulationEngine(&env); 

    GuiMain gui(simulationEngine); 
    gui.show(); 

    return app.exec(); 
}