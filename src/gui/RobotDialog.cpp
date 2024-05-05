/**
 * @file AutonomousRobot.cpp
 * @brief Definition of the AutonomousRobot class, which extends the Robot base class with specific functionalities for autonomous navigation and obstacle detection.
 *
 * @author Pavel Stepanov (xstepa77)
 * @author Gleb Litvinchuk (xlitvi02)
 * @date 2024-05-05
 */
#include "RobotDialog.h"

/**
 * @brief Constructor for the RobotDialog class.
 * @param clickPosition The position where the robot was clicked.
 * @param parent The parent widget.
 */
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

/**
 * @brief Getter for the ID of the robot.
 * @return The ID of the robot.
 */
int RobotDialog::getId() const {
    return idEdit->text().toInt();
}

/**
 * @brief Getter for the position of the robot.
 * @return The position of the robot.
 */
QPointF RobotDialog::getPosition() const {
    return QPointF(xEdit->text().toDouble(), yEdit->text().toDouble());
}

/**
 * @brief Getter for the speed of the robot.
 * @return The speed of the robot.
 */
double RobotDialog::getSpeed() const {
    return speedEdit->text().toDouble();
}

/**
 * @brief Getter for the orientation of the robot.
 * @return The orientation of the robot.
 */
double RobotDialog::getOrientation() const {
    return orientationEdit->text().toDouble();
}

/**
 * @brief Getter for the sensor size of the robot.
 * @return The sensor size of the robot.
 */
double RobotDialog::getSensorSize() const {
    return sensorSizeEdit->text().toDouble();
}

/**
 * @brief Setter for the initial values of the robot.
 * @param id The ID of the robot.
 * @param speed The speed of the robot.
 * @param orientation The orientation of the robot.
 * @param sensorSize The sensor size of the robot.
 * @param position The position of the robot.
 */
void RobotDialog::setInitialValues(int id, double speed, double orientation, double sensorSize, const QPointF& position) {
    if (speedEdit && orientationEdit && sensorSizeEdit) {
        idEdit->setText(QString::number(id));
        speedEdit->setText(QString::number(speed));
        orientationEdit->setText(QString::number(orientation));
        sensorSizeEdit->setText(QString::number(sensorSize));
        setInitialPosition(position);
    }
}

/**
 * @brief Setter for the initial position of the robot.
 * @param position The initial position of the robot.
 */
void RobotDialog::setInitialPosition(const QPointF &position) {
    xEdit->setText(QString::number(position.x()));
    yEdit->setText(QString::number(position.y()));
}
