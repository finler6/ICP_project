#include "LoadEnvironment.h"
#include "code/ConfigManager.h"
#include "code/AutonomousRobot.h"
#include "code/RemoteControlledRobot.h"
#include "code/Obstacle.h"
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QRegularExpression>
#include <memory>  // Include for std::make_unique

LoadEnvironment::LoadEnvironment(Environment* env, QObject* parent)
    : QObject(parent), environment(env) {}

void LoadEnvironment::loadNewConfiguration() {
    QString filePath = QFileDialog::getOpenFileName(nullptr, QObject::tr("Open configuration"), QDir::homePath(), QObject::tr("Configurations (*.txt)"));

    if (filePath.isEmpty()) {
        return;
    }

    emit stopEngine();
    environment->clear();
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("Could not open file: ") + filePath);
        emit stopEngine();
        return;
    }

    QTextStream in(&file);
    QString line;
    bool success = true;

    while (!in.atEnd()) {
        line = in.readLine();
        QStringList parts = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

        if (parts.count() > 1) {
            if (parts[0] == "Robot" && parts.count() >= 8) {
                QString robotType = parts[1];
                int id = parts[2].toInt();
                double x = parts[3].toDouble();
                double y = parts[4].toDouble();
                double speed = parts[5].toDouble();
                double direction = parts[6].toDouble();
                double sensorRange = parts[7].toDouble();

                if (robotType == "autonomous") {
                    auto robot = std::make_unique<AutonomousRobot>(id, std::make_pair(x, y), speed, direction, sensorRange, 800, 600, environment);
                    environment->addRobot(std::move(robot));
                } else if (robotType == "remote") {
                    auto robot = std::make_unique<RemoteControlledRobot>(id, std::make_pair(x, y), speed, direction, sensorRange, 800, 600, environment);
                    environment->addRobot(std::move(robot));
                }

            } else if (parts[0] == "Obstacle" && parts.count() == 5) {
                int id = parts[1].toInt();
                double x = parts[2].toDouble();
                double y = parts[3].toDouble();
                double size = parts[4].toDouble();

                auto obstacle = std::make_unique<Obstacle>(id, std::make_pair(x, y), size);
                environment->addObstacle(std::move(obstacle));

            } else {
                success = false;
                QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("Incorrect configuration string format: ") + line);
                break; 
            }
        }
    }

    file.close();

    if (success) {
        ConfigManager::setConfigPath(filePath);
    } else {
        environment->loadConfiguration("examples/example1.txt");
        emit stopEngine();
    }
}

