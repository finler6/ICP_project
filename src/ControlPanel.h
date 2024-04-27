#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class ControlPanel : public QWidget {
    Q_OBJECT

public:
    explicit ControlPanel(QWidget *parent = nullptr);

signals:
    void startSimulation();
    void pauseSimulation();
    void resumeSimulation();
    void stopSimulation();
    void continueSimulation();  // Add this signal
    void openSettings();        // Add this signal
    void loadnewConfiguration();   // Add this signal

private:
    QPushButton *startButton;
    QPushButton *pauseButton;
    QPushButton *resumeButton;
    QPushButton *stopButton;
    QPushButton *settingsButton;
    QPushButton *loadButton;
};

#endif // CONTROLPANEL_H

