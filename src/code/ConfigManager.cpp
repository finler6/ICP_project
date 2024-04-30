#include "ConfigManager.h"

QString ConfigManager::configPath = ""; // Инициализируем с пустой строкой

void ConfigManager::setConfigPath(const QString& path) {
    configPath = path;
}

const QString& ConfigManager::getConfigPath() {
    return configPath;
}
