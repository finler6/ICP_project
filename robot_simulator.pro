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
           src/GUI.cpp \
           src/SimulationEngine.cpp \
           src/Utilities.cpp

HEADERS += src/Robot.h \
           src/AutonomousRobot.h \
           src/RemoteControlledRobot.h \
           src/Environment.h \
           src/Obstacle.h \
           src/GUI.h \
           src/SimulationEngine.h \
           src/Utilities.h

