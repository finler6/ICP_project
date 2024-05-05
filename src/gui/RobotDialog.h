/**
 * @file AutonomousRobot.cpp
 * @brief Definition of the AutonomousRobot class, which extends the Robot base class with specific functionalities for autonomous navigation and obstacle detection.
 *
 * @author Pavel Stepanov (xstepa77)
 * @author Gleb Litvinchuk (xlitvi02)
 * @date 2024-05-05
 */
#ifndef ROBOTDIALOG_H
#define ROBOTDIALOG_H

#include "QDialog"
#include "QLineEdit"
#include "QFormLayout"
#include "QDialogButtonBox"
#include "QLabel"
#include "QComboBox"
#include "QDoubleValidator"
#include "QIntValidator"
#include "QPointF"
#include "SimulationWindow.h"

/**
 * @brief Dialog for creating a new robot.
 */
class RobotDialog : public QDialog {
    Q_OBJECT

public:
    explicit RobotDialog(const QPointF& clickPosition, QWidget *parent = nullptr);

    [[nodiscard]] QString getType() const;
    [[nodiscard]] QPointF getPosition() const;

    [[nodiscard]] int getId() const;

    [[nodiscard]] double getSpeed() const;
    [[nodiscard]] double getSensorSize() const;
    [[nodiscard]] double getOrientation() const;

    void setInitialPosition(const QPointF &position);
    void setInitialValues(int id, double speed, double orientation, double sensorSize, const QPointF& position);

private:
    QComboBox *typeEdit;
    QLineEdit *idEdit;
    QLineEdit *xEdit;
    QLineEdit *yEdit;
    QLineEdit *speedEdit;
    QLineEdit *orientationEdit;
    QLineEdit *sensorSizeEdit;
};

#endif // ROBOTDIALOG_H
