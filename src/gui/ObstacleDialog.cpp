#include "ObstacleDialog.h"

ObstacleDialog::ObstacleDialog(QWidget *parent) : QDialog(parent) {
    idEdit = new QLineEdit(this);
    xEdit = new QLineEdit(this);
    yEdit = new QLineEdit(this);
    sizeEdit = new QLineEdit(this);

    idEdit->setValidator(new QIntValidator(this));
    xEdit->setValidator(new QDoubleValidator(this));
    yEdit->setValidator(new QDoubleValidator(this));
    sizeEdit->setValidator(new QDoubleValidator(this));

    QLabel *idLabel = new QLabel(tr("ID:"), this);
    QLabel *xLabel = new QLabel(tr("X Coordinate:"), this);
    QLabel *yLabel = new QLabel(tr("Y Coordinate:"), this);
    QLabel *sizeLabel = new QLabel(tr("Size:"), this);

    QFormLayout *layout = new QFormLayout();
    layout->addRow(idLabel, idEdit);
    layout->addRow(xLabel, xEdit);
    layout->addRow(yLabel, yEdit);
    layout->addRow(sizeLabel, sizeEdit);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    layout->addWidget(buttonBox);
    setLayout(layout);

    setWindowTitle(tr("Create Obstacle"));
}

int ObstacleDialog::getId() const {
    return idEdit->text().toInt();
}

QPointF ObstacleDialog::getPosition() const {
    return QPointF(xEdit->text().toDouble(), yEdit->text().toDouble());
}

double ObstacleDialog::getSize() const {
    return sizeEdit->text().toDouble();
}

void ObstacleDialog::setInitialSize(double size) {
    sizeEdit->setText(QString::number(size));
}


