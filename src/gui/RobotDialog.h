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

class RobotDialog : public QDialog {
    Q_OBJECT

public:
    explicit RobotDialog(QWidget *parent = nullptr);
    QString getType() const;
    int getId() const;
    QPointF getPosition() const;
    double getSpeed() const;
    double getOrientation() const;
    double getSensorSize() const;
    void setInitialValues(double speed, double orientation, double sensorSize);
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
