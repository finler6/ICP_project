#ifndef OBSTACLEDIALOG_H
#define OBSTACLEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include <QIntValidator>
#include <QDoubleValidator>

class ObstacleDialog : public QDialog {
    Q_OBJECT

public:
    explicit ObstacleDialog(QWidget *parent = nullptr);
    int getId() const;
    QPointF getPosition() const;
    double getSize() const;
    void setInitialSize(double size);

private:
    QLineEdit *idEdit;
    QLineEdit *xEdit;
    QLineEdit *yEdit;
    QLineEdit *sizeEdit;
};

#endif 
