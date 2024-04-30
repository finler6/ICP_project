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
    // Создаем таблицу для роботов
    robotTable = new QTableWidget(0, 7); // 7 столбцов для параметров робота
    QStringList robotHeaders{"Тип", "ID", "X", "Y", "Скорость", "Направление", "Дальность сенсоров"};
    robotTable->setHorizontalHeaderLabels(robotHeaders);
    robotTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mainLayout->addWidget(new QLabel("Роботы:"));
    mainLayout->addWidget(robotTable);

    // Кнопки для управления списком роботов
    QHBoxLayout *robotButtonsLayout = new QHBoxLayout();
    addRobotButton = new QPushButton("Добавить робота");
    removeRobotButton = new QPushButton("Удалить робота");
    robotButtonsLayout->addWidget(addRobotButton);
    robotButtonsLayout->addWidget(removeRobotButton);
    mainLayout->addLayout(robotButtonsLayout);
    connect(addRobotButton, &QPushButton::clicked, this, &SettingsDialog::addRobot);
    connect(removeRobotButton, &QPushButton::clicked, this, &SettingsDialog::removeRobot);

    // Создаем таблицу для препятствий
    obstacleTable = new QTableWidget(0, 4); // 3 столбца для параметров препятствия
    QStringList obstacleHeaders{"Id","X", "Y", "Размер"};
    obstacleTable->setHorizontalHeaderLabels(obstacleHeaders);
    obstacleTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mainLayout->addWidget(new QLabel("Препятствия:"));
    mainLayout->addWidget(obstacleTable);

    // Кнопки для управления списком препятствий
    QHBoxLayout *obstacleButtonsLayout = new QHBoxLayout();
    addObstacleButton = new QPushButton("Добавить препятствие");
    removeObstacleButton = new QPushButton("Удалить препятствие");
    obstacleButtonsLayout->addWidget(addObstacleButton);
    obstacleButtonsLayout->addWidget(removeObstacleButton);
    mainLayout->addLayout(obstacleButtonsLayout);
    connect(addObstacleButton, &QPushButton::clicked, this, &SettingsDialog::addObstacle);
    connect(removeObstacleButton, &QPushButton::clicked, this, &SettingsDialog::removeObstacle);

    // Добавляем кнопки для сохранения и отмены
    filenameEdit = new QLineEdit(this);
    filenameEdit->setPlaceholderText("Введите имя файла");
    QHBoxLayout *filenameLayout = new QHBoxLayout();
    filenameLayout->addWidget(new QLabel("Имя файла:"));
    filenameLayout->addWidget(filenameEdit);
    mainLayout->addLayout(filenameLayout);

    QHBoxLayout *saveCancelLayout = new QHBoxLayout();
    saveButton = new QPushButton("Сохранить");
    cancelButton = new QPushButton("Отмена");
    saveCancelLayout->addWidget(saveButton);
    saveCancelLayout->addWidget(cancelButton);
    mainLayout->addLayout(saveCancelLayout);
    connect(saveButton, &QPushButton::clicked, this, &SettingsDialog::saveSettings);
    connect(cancelButton, &QPushButton::clicked, this, &SettingsDialog::reject);

    setLayout(mainLayout);
    setWindowTitle("Настройки симуляции");
}

void SettingsDialog::addRobot() {
    int row = robotTable->rowCount();
    robotTable->insertRow(row);
    // Начальные значения для новой строки, можно адаптировать под свои нужды
    robotTable->setItem(row, 0, new QTableWidgetItem("autonomous"));  // Тип робота
    robotTable->setItem(row, 1, new QTableWidgetItem(QString::number(row)));  // ID робота, например
    robotTable->setItem(row, 2, new QTableWidgetItem("0"));  // X координата
    robotTable->setItem(row, 3, new QTableWidgetItem("0"));  // Y координата
    robotTable->setItem(row, 4, new QTableWidgetItem("1.0"));  // Скорость
    robotTable->setItem(row, 5, new QTableWidgetItem("0"));  // Направление
    robotTable->setItem(row, 6, new QTableWidgetItem("100"));  // Дальность сенсоров
}

void SettingsDialog::addObstacle() {
    int row = obstacleTable->rowCount();
    obstacleTable->insertRow(row);
    obstacleTable->setItem(row, 0, new QTableWidgetItem(QString::number(row)));  // X координата
    obstacleTable->setItem(row, 1, new QTableWidgetItem("100"));  // X координата
    obstacleTable->setItem(row, 2, new QTableWidgetItem("100"));  // Y координата
    obstacleTable->setItem(row, 3, new QTableWidgetItem("10"));  // Размер
}


void SettingsDialog::removeRobot() {
    int row = robotTable->currentRow();
    if (row >= 0 && QMessageBox::question(this, tr("Удалить робота"), tr("Вы уверены, что хотите удалить этого робота?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        robotTable->removeRow(row);
    }
}

void SettingsDialog::removeObstacle() {
    int row = obstacleTable->currentRow();
    if (row >= 0 && QMessageBox::question(this, tr("Удалить препятствие"), tr("Вы уверены, что хотите удалить это препятствие?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        obstacleTable->removeRow(row);
    }
}
void SettingsDialog::saveSettings() {
    QString directory = QFileDialog::getExistingDirectory(this, tr("Выберите папку для сохранения"), QDir::homePath());
    
    if (!directory.isEmpty()) {
        QString filePath = directory + "/" + filenameEdit->text().trimmed() + ".txt";
        QFile file(filePath);
        
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);

            // Сохраняем данные о роботах
            for (int row = 0; row < robotTable->rowCount(); ++row) {
                out << "Robot";
                for (int col = 0; col < robotTable->columnCount(); ++col) {
                    QTableWidgetItem* item = robotTable->item(row, col);
                    out << " " << (item ? item->text() : "undefined");
                }
                out << "\n";
            }

            // Сохраняем данные о препятствиях
            for (int row = 0; row < obstacleTable->rowCount(); ++row) {
                out << "Obstacle";
                for (int col = 0; col < obstacleTable->columnCount(); ++col) {
                    QTableWidgetItem* item = obstacleTable->item(row, col);
                    out << " " << (item ? item->text() : "undefined");
                }
                out << "\n";
            }

            file.close();
            QMessageBox::information(this, tr("Файл сохранён"), tr("Файл успешно сохранён в: ") + filePath);
            accept(); // Закрываем диалог с сохранением
        } else {
            QMessageBox::critical(this, tr("Ошибка сохранения"), tr("Не удалось сохранить файл в: ") + filePath);
            reject(); // Закрываем диалог без сохранения изменений
        }
    }
}



void SettingsDialog::cancel() {
    reject(); // Закрываем диалог без сохранения изменений
}