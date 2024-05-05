/**
 * @file main.cpp
 * @brief Entry point for the robot simulation program.
 *
 * This file initializes the QApplication, loads configuration settings, sets up the simulation environment,
 * and launches the graphical user interface for the robot simulation. It serves as the starting point for the
 * entire application.
 * @author Pavel Stepanov (xstepa77)
 * @author Gleb Litvinchuk (xlitvi02)
 * @date 2024-05-05
 */

#include <QApplication>
#include "gui/GuiMain.h"
#include "Environment.h"
#include "SimulationEngine.h"
#include "ConfigManager.h"
#include <QString>
#include <string>

/**
 * @brief Main function that sets up and runs the robot simulation application.
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return Returns the exit status of the application.
 *
 * The function initializes a QApplication, loads configuration from a specified path,
 * initializes the simulation environment and engine, sets up the GUI, and finally enters the main event loop of the application.
 */
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);  /// Create an application instance with command-line arguments.

    ConfigManager::setConfigPath("examples/example1.txt");  /// Set the configuration file path.
    Environment env;  /// Create an instance of Environment.
    QString qPath = ConfigManager::getConfigPath();  /// Retrieve the configuration path as a QString.
    std::string path = qPath.toStdString();  /// Convert QString path to std::string.
    env.loadConfiguration(path);  /// Load configuration settings into the environment.

    SimulationEngine *simulationEngine = new SimulationEngine(&env);  /// Initialize the simulation engine with the environment.

    GuiMain gui(simulationEngine);  /// Create the main GUI window with the simulation engine.
    gui.show();  /// Display the GUI window.

    return app.exec();  /// Enter the main event loop of the application.
}