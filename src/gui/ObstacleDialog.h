#ifndef OBSTACLEDIALOG_H
#define OBSTACLEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QPointF>
#include "SimulationWindow.h"

class ObstacleDialog : public QDialog {
    Q_OBJECT

public:
    explicit ObstacleDialog(const QPointF& clickPosition, QWidget *parent = nullptr);
    int getId() const;
    QPointF getPosition() const;
    double getSize() const;
    void setInitialSize(int id, double size, const QPointF& position);

private:
    QLineEdit *idEdit;
    QLineEdit *xEdit;
    QLineEdit *yEdit;
    QLineEdit *sizeEdit;
};

#endif 
