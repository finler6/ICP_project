TEMPLATE = app
TARGET = robot_simulator
CONFIG += c++17
QT += core gui widgets

INCLUDEPATH += ./src \
               /usr/include/x86_64-linux-gnu/qt5

SOURCES += src/main.cpp \
           src/Robot.cpp \
           src/AutonomousRobot.cpp \
           src/RemoteControlledRobot.cpp \
           src/Environment.cpp \
           src/Obstacle.cpp \
           src/SimulationEngine.cpp \
           src/Utilities.cpp \
           src/SimulationWindow.cpp \
           src/SettingsDialog.cpp \
           src/RobotView.cpp \
           src/ObstacleView.cpp \
           src/GuiMain.cpp \
           src/ControlPanel.cpp \
           src/MapEditor.cpp \
           src/LoadEnvironment.cpp


HEADERS += src/Robot.h \
           src/AutonomousRobot.h \
           src/RemoteControlledRobot.h \
           src/Environment.h \
           src/Obstacle.h \
           src/SimulationEngine.h \
           src/Utilities.h \
           src/SimulationWindow.h \
           src/SettingsDialog.h \
           src/RobotView.h \
           src/ObstacleView.h \
           src/GuiMain.h \
           src/ControlPanel.h \
           src/MapEditor.h \
           src/LoadEnvironment.h