TEMPLATE = app
TARGET = robot_simulator
CONFIG += c++17
QT += core gui widgets

INCLUDEPATH += ./src \
               /usr/include/x86_64-linux-gnu/qt5

SOURCES += src/code/main.cpp \
           src/code/Robot.cpp \
           src/code/AutonomousRobot.cpp \
           src/code/RemoteControlledRobot.cpp \
           src/code/Environment.cpp \
           src/code/Obstacle.cpp \
           src/code/SimulationEngine.cpp \
           src/code/Utilities.cpp \
           src/gui/SimulationWindow.cpp \
           src/gui/SettingsDialog.cpp \
           src/gui/RobotView.cpp \
           src/gui/ObstacleView.cpp \
           src/gui/GuiMain.cpp \
           src/gui/ControlPanel.cpp \
           src/gui/MapEditor.cpp \
           src/gui/LoadEnvironment.cpp


HEADERS += src/code/Robot.h \
           src/code/AutonomousRobot.h \
           src/code/RemoteControlledRobot.h \
           src/code/Environment.h \
           src/code/Obstacle.h \
           src/code/SimulationEngine.h \
           src/code/Utilities.h \
           src/gui/SimulationWindow.h \
           src/gui/SettingsDialog.h \
           src/gui/RobotView.h \
           src/gui/ObstacleView.h \
           src/gui/GuiMain.h \
           src/gui/ControlPanel.h \
           src/gui/MapEditor.h \
           src/gui/LoadEnvironment.h