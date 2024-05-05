/**
 * @file ConfigManager.h
 * @brief Singleton class to manage configuration paths for the application.
 *
 * This class provides methods to set and retrieve the global configuration path used across the application.
 * It uses a static member to store the path, ensuring it is accessible from any point in the application without instantiation.
  * @author Pavel Stepanov (xstepa77)
 * @author Gleb Litvinchuk (xlitvi02)
 * @date 2024-05-05
 */

#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QString>

/**
 * @class ConfigManager
 * @brief Manages the configuration path for the application.
 *
 * ConfigManager uses static methods to manipulate and retrieve the configuration path,
 * ensuring that all parts of the application can access consistent configuration data.
 */
class ConfigManager {
public:
    /**
     * @brief Sets the configuration path for the application.
     * @param path The configuration path to be set.
     */
    static void setConfigPath(const QString& path);

    /**
     * @brief Retrieves the current configuration path.
     * @return The current configuration path as a const reference to QString.
     */
    static const QString& getConfigPath();

private:
    static QString configPath; ///< Static variable to hold the configuration path.
};

#endif // CONFIGMANAGER_H

