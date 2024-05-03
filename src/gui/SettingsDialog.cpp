#include "SettingsDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    robotTable = new QTableWidget(0, 7); 
    QStringList robotHeaders{"Type", "ID", "X", "Y", "Velocity", "Orientation", "Sensor Range"};
    robotTable->setHorizontalHeaderLabels(robotHeaders);
    robotTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mainLayout->addWidget(new QLabel("Robots: "));
    mainLayout->addWidget(robotTable);

    QHBoxLayout *robotButtonsLayout = new QHBoxLayout();
    addRobotButton = new QPushButton("Add Robot");
    removeRobotButton = new QPushButton("Delete Robot");
    robotButtonsLayout->addWidget(addRobotButton);
    robotButtonsLayout->addWidget(removeRobotButton);
    mainLayout->addLayout(robotButtonsLayout);
    connect(addRobotButton, &QPushButton::clicked, this, &SettingsDialog::addRobot);
    connect(removeRobotButton, &QPushButton::clicked, this, &SettingsDialog::removeRobot);

    obstacleTable = new QTableWidget(0, 4); 
    QStringList obstacleHeaders{"ID","X", "Y", "Size"};
    obstacleTable->setHorizontalHeaderLabels(obstacleHeaders);
    obstacleTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mainLayout->addWidget(new QLabel("Obstacles:"));
    mainLayout->addWidget(obstacleTable);

    QHBoxLayout *obstacleButtonsLayout = new QHBoxLayout();
    addObstacleButton = new QPushButton("Add Obstacle");
    removeObstacleButton = new QPushButton("Remove Obstacle");
    obstacleButtonsLayout->addWidget(addObstacleButton);
    obstacleButtonsLayout->addWidget(removeObstacleButton);
    mainLayout->addLayout(obstacleButtonsLayout);
    connect(addObstacleButton, &QPushButton::clicked, this, &SettingsDialog::addObstacle);
    connect(removeObstacleButton, &QPushButton::clicked, this, &SettingsDialog::removeObstacle);

    filenameEdit = new QLineEdit(this);
    filenameEdit->setPlaceholderText("Enter a filename");
    QHBoxLayout *filenameLayout = new QHBoxLayout();
    filenameLayout->addWidget(new QLabel("Filename:"));
    filenameLayout->addWidget(filenameEdit);
    mainLayout->addLayout(filenameLayout);

    QHBoxLayout *saveCancelLayout = new QHBoxLayout();
    saveButton = new QPushButton("Save");
    cancelButton = new QPushButton("Cancel");
    saveCancelLayout->addWidget(saveButton);
    saveCancelLayout->addWidget(cancelButton);
    mainLayout->addLayout(saveCancelLayout);
    connect(saveButton, &QPushButton::clicked, this, &SettingsDialog::saveSettings);
    connect(cancelButton, &QPushButton::clicked, this, &SettingsDialog::reject);

    setLayout(mainLayout);
    setWindowTitle("Configuration Editor");
}

void SettingsDialog::addRobot() {
    int row = robotTable->rowCount();
    robotTable->insertRow(row);
    robotTable->setItem(row, 0, new QTableWidgetItem("autonomous"));  
    robotTable->setItem(row, 1, new QTableWidgetItem(QString::number(row)));  
    robotTable->setItem(row, 2, new QTableWidgetItem("0"));  
    robotTable->setItem(row, 3, new QTableWidgetItem("0"));  
    robotTable->setItem(row, 4, new QTableWidgetItem("1.0"));  
    robotTable->setItem(row, 5, new QTableWidgetItem("0"));  
    robotTable->setItem(row, 6, new QTableWidgetItem("100"));  
}

void SettingsDialog::addObstacle() {
    int row = obstacleTable->rowCount();
    obstacleTable->insertRow(row);
    obstacleTable->setItem(row, 0, new QTableWidgetItem(QString::number(row)));  
    obstacleTable->setItem(row, 1, new QTableWidgetItem("100"));  
    obstacleTable->setItem(row, 2, new QTableWidgetItem("100"));  
    obstacleTable->setItem(row, 3, new QTableWidgetItem("10"));  
}


void SettingsDialog::removeRobot() {
    int row = robotTable->currentRow();
    if (row >= 0 && QMessageBox::question(this, tr("Delete Robot"), tr("Are you sure you want to delete this Robot?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        robotTable->removeRow(row);
    }
}

void SettingsDialog::removeObstacle() {
    int row = obstacleTable->currentRow();
    if (row >= 0 && QMessageBox::question(this, tr("Delete Obstacle"), tr("Are you sure you want to delete this Obstacle?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        obstacleTable->removeRow(row);
    }
}
void SettingsDialog::saveSettings() {
    QString directory = QFileDialog::getExistingDirectory(this, tr("Select a folder to save"), QDir::homePath());
    
    if (!directory.isEmpty()) {
        QString filePath = directory + "/" + filenameEdit->text().trimmed() + ".txt";
        QFile file(filePath);
        
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            for (int row = 0; row < robotTable->rowCount(); ++row) {
                out << "Robot";
                for (int col = 0; col < robotTable->columnCount(); ++col) {
                    QTableWidgetItem* item = robotTable->item(row, col);
                    out << " " << (item ? item->text() : "undefined");
                }
                out << "\n";
            }
            for (int row = 0; row < obstacleTable->rowCount(); ++row) {
                out << "Obstacle";
                for (int col = 0; col < obstacleTable->columnCount(); ++col) {
                    QTableWidgetItem* item = obstacleTable->item(row, col);
                    out << " " << (item ? item->text() : "undefined");
                }
                out << "\n";
            }

            file.close();
            QMessageBox::information(this, tr("File saved"), tr("The file was successfully saved in: ") + filePath);
            accept(); 
        } else {
            QMessageBox::critical(this, tr("Save error"), tr("Could not save file to: ") + filePath);
            reject(); 
        }
    }
}



void SettingsDialog::cancel() {
    reject(); 
}