// SettingsDialog.h
#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QGroupBox>
#include <QDialog>
#include <QPushButton>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QListWidget>
#include <QTableWidget>

class SettingsDialog : public QDialog {
    Q_OBJECT

public:
    SettingsDialog(QWidget *parent = nullptr);
private:
    QTableWidget* robotTable;
    QTableWidget* obstacleTable;
    QPushButton* addRobotButton;
    QPushButton* removeRobotButton;
    QPushButton* addObstacleButton;
    QPushButton* removeObstacleButton;
    QLineEdit* speedEdit;
    QLineEdit* robotTypeEdit;
    QLineEdit* robotIdEdit;
    QLineEdit* robotXEdit;
    QLineEdit* robotYEdit;
    QLineEdit* robotSpeedEdit;
    QLineEdit* robotDirectionEdit;
    QLineEdit* robotRangeEdit;
    QLineEdit* obstacleXEdit;
    QLineEdit* obstacleYEdit;
    QLineEdit* obstacleSizeEdit;
    QLineEdit* filenameEdit;
    QPushButton* saveButton;
    QPushButton* cancelButton;
    QGroupBox* speedGroup;
    QGroupBox* robotGroup;
    QGroupBox* obstacleGroup;

    void addRobot();
    void removeRobot();
    void addObstacle();
    void removeObstacle();
    void saveSettings();
    void cancel();
};

#endif // SETTINGSDIALOG_H