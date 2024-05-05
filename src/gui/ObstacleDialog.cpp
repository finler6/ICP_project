/**
 * @file AutonomousRobot.cpp
 * @brief Definition of the AutonomousRobot class, which extends the Robot base class with specific functionalities for autonomous navigation and obstacle detection.
 *
 * @author Pavel Stepanov (xstepa77)
 * @author Gleb Litvinchuk (xlitvi02)
 * @date 2024-05-05
 */
#include "ObstacleDialog.h"

/**
 * @brief Constructor for the ObstacleDialog class.
 * @param clickPosition The position where the user clicked on the map.
 * @param parent The parent widget.
 */
ObstacleDialog::ObstacleDialog(const QPointF& clickPosition, QWidget *parent) : QDialog(parent) {
    idEdit = new QLineEdit(this);
    xEdit = new QLineEdit(QString::number(clickPosition.x()), this);
    yEdit = new QLineEdit(QString::number(clickPosition.y()), this);
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

/**
 * @brief Get the ID of the obstacle.
 * @return The ID of the obstacle.
 */
int ObstacleDialog::getId() const {
    return idEdit->text().toInt();
}

/**
 * @brief Get the position of the obstacle.
 * @return The position of the obstacle.
 */
QPointF ObstacleDialog::getPosition() const {
    return QPointF(xEdit->text().toDouble(), yEdit->text().toDouble());
}

/**
 * @brief Get the size of the obstacle.
 * @return The size of the obstacle.
 */
double ObstacleDialog::getSize() const {
    return sizeEdit->text().toDouble();
}

/**
 * @brief Set the initial size of the obstacle.
 * @param id The ID of the obstacle.
 * @param size The size of the obstacle.
 * @param position The position of the obstacle.
 */
void ObstacleDialog::setInitialSize(int id, double size, const QPointF& position) {
    sizeEdit->setText(QString::number(size));
    idEdit->setText(QString::number(id));
    xEdit->setText(QString::number(position.x()));
    yEdit->setText(QString::number(position.y()));
}


