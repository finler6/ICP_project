#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QString>

class ConfigManager {
public:
    static void setConfigPath(const QString& path);
    static const QString& getConfigPath();

private:
    static QString configPath;
};

#endif // CONFIGMANAGER_H
