#include "ConfigManager.h"

QString ConfigManager::configPath = ""; 

void ConfigManager::setConfigPath(const QString& path) {
    configPath = path;
}

const QString& ConfigManager::getConfigPath() {
    return configPath;
}
