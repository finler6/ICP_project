/**
 * @file ConfigManager.cpp
 * @brief Implements the configuration management functions defined in ConfigManager.h.
 *
 * This file provides the definition of the static methods and variables used to manage the configuration path.
 * @author Pavel Stepanov (xstepa77)
 * @author Gleb Litvinchuk (xlitvi02)
 * @date 2024-05-05
 */

#include "ConfigManager.h"

// Initialize the static member of ConfigManager class.
QString ConfigManager::configPath = "";

/**
 * @brief Sets the configuration path to a new value.
 * @param path A QString representing the new configuration path.
 *
 * This method updates the static configuration path used by the application.
 */
void ConfigManager::setConfigPath(const QString& path) {
    configPath = path;
}

/**
 * @brief Retrieves the configuration path set for the application.
 * @return A constant reference to a QString holding the configuration path.
 *
 * This method returns the current value of the configuration path, allowing other parts of the application to access configuration data.
 */
const QString& ConfigManager::getConfigPath() {
    return configPath;
}

