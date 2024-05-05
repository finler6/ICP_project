/**
 * @file AutonomousRobot.cpp
 * @brief Definition of the AutonomousRobot class, which extends the Robot base class with specific functionalities for autonomous navigation and obstacle detection.
 *
 * @author Pavel Stepanov (xstepa77)
 * @author Gleb Litvinchuk (xlitvi02)
 * @date 2024-05-05
 */
#ifndef OBSTACLEDIALOG_H
#define OBSTACLEDIALOG_H

#include "SimulationWindow.h"
#include "QDialog"
#include "QLineEdit"
#include "QFormLayout"
#include "QDialogButtonBox"
#include "QLabel"
#include "QIntValidator"
#include "QDoubleValidator"
#include "QPointF"

/**
 * @brief The ObstacleDialog class represents a dialog window for creating and editing obstacles.
 */
class ObstacleDialog : public QDialog {
    Q_OBJECT

public:
    explicit ObstacleDialog(const QPointF& clickPosition, QWidget *parent = nullptr);

    [[nodiscard]] int getId() const;
    [[nodiscard]] double getSize() const;
    [[nodiscard]] QPointF getPosition() const;
    void setInitialSize(int id, double size, const QPointF& position);

private:
    QLineEdit *idEdit;
    QLineEdit *xEdit;
    QLineEdit *yEdit;
    QLineEdit *sizeEdit;
};

#endif 
