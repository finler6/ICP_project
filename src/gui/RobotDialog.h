#ifndef ROBOTDIALOG_H
#define ROBOTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include <QComboBox>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QPointF>
#include "SimulationWindow.h"

class RobotDialog : public QDialog {
    Q_OBJECT

public:
    explicit RobotDialog(const QPointF& clickPosition, QWidget *parent = nullptr);
    QString getType() const;
    int getId() const;
    QPointF getPosition() const;
    double getSpeed() const;
    double getOrientation() const;
    double getSensorSize() const;
    void setInitialValues(int id, double speed, double orientation, double sensorSize, const QPointF& position);
    void setInitialPosition(const QPointF &position);
    void setInitialId(int id);

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
