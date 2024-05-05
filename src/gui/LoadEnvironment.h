/**
 * @file AutonomousRobot.cpp
 * @brief Definition of the AutonomousRobot class, which extends the Robot base class with specific functionalities for autonomous navigation and obstacle detection.
 *
 * @author Pavel Stepanov (xstepa77)
 * @author Gleb Litvinchuk (xlitvi02)
 * @date 2024-05-05
 */
#include "code/Environment.h"
#include "QObject"
#include "QFileDialog"
#include "QTextStream"
#include "QMessageBox"
#include "QRegularExpression"
#include "memory"

/**
 * @brief The LoadEnvironment class is responsible for loading a new environment configuration from a file.
 */
class LoadEnvironment : public QObject {
    Q_OBJECT

public:
    explicit LoadEnvironment(Environment* environment, QObject* parent = nullptr);

public slots:
    void loadNewConfiguration();

signals:
    void stopEngine();

private:
    Environment* environment;
};
