#include "LoadEnvironment.h"
#include "code/AutonomousRobot.h"
#include "code/RemoteControlledRobot.h"
#include "code/Obstacle.h"
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

LoadEnvironment::LoadEnvironment(Environment* env, QObject* parent)
    : QObject(parent), environment(env) {}

void LoadEnvironment::loadNewConfiguration() {
    // Пользователь выбирает файл конфигурации через диалог
    QString filePath = QFileDialog::getOpenFileName(nullptr, QObject::tr("Открыть конфигурацию"), QDir::homePath(), QObject::tr("Конфигурации (*.txt)"));

    if (filePath.isEmpty()) {
        return; // Если файл не выбран, отправляем сигнал и выходим
    }

    // Остановка движка перед загрузкой новой конфигурации
    emit stopEngine();

    // Сброс текущего состояния окружения
    environment->clear();

    // Попытка загрузить новую конфигурацию из выбранного файла
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, QObject::tr("Ошибка"), QObject::tr("Не удалось открыть файл: ") + filePath);
        emit stopEngine();
        return;
    }

    QTextStream in(&file);
    QString line;
    bool success = true;

    while (!in.atEnd()) {
        line = in.readLine();
        QStringList parts = line.split(QRegExp("\\s+"), Qt::SkipEmptyParts);

        if (parts.count() > 1) {
            if (parts[0] == "Robot" && parts.count() >= 7) {
                // Допустим, что порядок данных следующий: "Robot Type ID X Y Speed Direction SensorRange"
                QString robotType = parts[1];
                int id = parts[2].toInt();
                double x = parts[3].toDouble();
                double y = parts[4].toDouble();
                double speed = parts[5].toDouble();
                double direction = parts[6].toDouble();
                double sensorRange = parts[7].toDouble();

                Robot* robot = nullptr;
                if (robotType == "autonomous") {
                    robot = new AutonomousRobot(id, std::make_pair(x, y), speed, direction, sensorRange);
                } else if (robotType == "remote") {
                    robot = new RemoteControlledRobot(id, std::make_pair(x, y), speed, direction, sensorRange);
                }

                if (robot) {
                    environment->addRobot(robot);
                } else {
                    success = false;
                    QMessageBox::critical(nullptr, QObject::tr("Ошибка"), QObject::tr("Невозможно создать робота с типом: ") + robotType);
                    break;
                }

            } else if (parts[0] == "Obstacle" && parts.count() == 5) {
                // Порядок данных: "Obstacle id X Y Size"
                int id = parts[1].toInt();
                double x = parts[2].toDouble();
                double y = parts[3].toDouble();
                double size = parts[4].toDouble();

                Obstacle obstacle(id, std::make_pair(x, y), size);
                environment->addObstacle(obstacle);

            } else {
                success = false;
                QMessageBox::critical(nullptr, QObject::tr("Ошибка"), QObject::tr("Некорректный формат строки конфигурации: ") + line);
                break; // Прерываем чтение файла
            }
        }
    }

    file.close();

    if (success) {
    } else {
        // При ошибке загрузки восстанавливаем стандартную конфигурацию
        environment->loadConfiguration("examples/example1.txt");
        emit stopEngine();
    }
}

