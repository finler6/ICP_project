#include <QApplication>
#include "gui/GuiMain.h"
#include "Environment.h"
#include "SimulationEngine.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    Environment env; // Assuming Environment handles configurations itself or via a method
    env.loadConfiguration("examples/example1.txt"); // Load configuration for the simulation

    SimulationEngine *simulationEngine = new SimulationEngine(&env); // Create the simulation engine with the environment

    GuiMain gui(simulationEngine); // Pass the simulation engine to the GUI
    gui.show(); // Show the main window

    return app.exec(); // Start the Qt event loop
}