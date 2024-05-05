#include "RobotDialog.h"

RobotDialog::RobotDialog(const QPointF& clickPosition, QWidget *parent) : QDialog(parent) {
    typeEdit = new QComboBox(this);
    typeEdit->addItem("autonomous");
    typeEdit->addItem("remote");

    idEdit = new QLineEdit(this);
    xEdit = new QLineEdit(QString::number(clickPosition.x()), this);  // Set initial X coordinate
    yEdit = new QLineEdit(QString::number(clickPosition.y()), this);
    speedEdit = new QLineEdit(this);
    orientationEdit = new QLineEdit(this);
    sensorSizeEdit = new QLineEdit(this);

    idEdit->setValidator(new QIntValidator(this));
    xEdit->setValidator(new QDoubleValidator(this));
    yEdit->setValidator(new QDoubleValidator(this));
    speedEdit->setValidator(new QDoubleValidator(this));
    orientationEdit->setValidator(new QDoubleValidator(this));
    sensorSizeEdit->setValidator(new QDoubleValidator(this));

    QLabel *typeLabel = new QLabel(tr("Type:"), this);
    QLabel *idLabel = new QLabel(tr("ID:"), this);
    QLabel *xLabel = new QLabel(tr("X Coordinate:"), this);
    QLabel *yLabel = new QLabel(tr("Y Coordinate:"), this);
    QLabel *speedLabel = new QLabel(tr("Speed:"), this);
    QLabel *orientationLabel = new QLabel(tr("Orientation:"), this);
    QLabel *sensorSizeLabel = new QLabel(tr("Sensor Size:"), this);

    QFormLayout *layout = new QFormLayout();
    layout->addRow(typeLabel, typeEdit);
    layout->addRow(idLabel, idEdit);
    layout->addRow(xLabel, xEdit);
    layout->addRow(yLabel, yEdit);
    layout->addRow(speedLabel, speedEdit);
    layout->addRow(orientationLabel, orientationEdit);
    layout->addRow(sensorSizeLabel, sensorSizeEdit);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    layout->addWidget(buttonBox);
    setLayout(layout);

    setWindowTitle(tr("Create Robot"));
}

QString RobotDialog::getType() const {
    return typeEdit->currentText();
}

int RobotDialog::getId() const {
    return idEdit->text().toInt();
}

QPointF RobotDialog::getPosition() const {
    return QPointF(xEdit->text().toDouble(), yEdit->text().toDouble());
}

double RobotDialog::getSpeed() const {
    return speedEdit->text().toDouble();
}

double RobotDialog::getOrientation() const {
    return orientationEdit->text().toDouble();
}

double RobotDialog::getSensorSize() const {
    return sensorSizeEdit->text().toDouble();
}

void RobotDialog::setInitialValues(int id, double speed, double orientation, double sensorSize, const QPointF& position) {
    if (speedEdit && orientationEdit && sensorSizeEdit) {
        idEdit->setText(QString::number(id));
        speedEdit->setText(QString::number(speed));
        orientationEdit->setText(QString::number(orientation));
        sensorSizeEdit->setText(QString::number(sensorSize));
        setInitialPosition(position);
    } else {
        qDebug() << "One of the edits is not initialized";
    }
}


void RobotDialog::setInitialPosition(const QPointF &position) {
    xEdit->setText(QString::number(position.x()));
    yEdit->setText(QString::number(position.y()));
}

void RobotDialog::setInitialId(int id) {
    idEdit->setText(QString::number(id));
}
