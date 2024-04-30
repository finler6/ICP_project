TEMPLATE = app
TARGET = robot_simulator
CONFIG += c++17
QT += core gui widgets

INCLUDEPATH += ./src \
               /usr/include/x86_64-linux-gnu/qt5

SOURCES += src/code/*.cpp \
           src/gui/*.cpp


HEADERS += src/code/*.h \
           src/gui/*.h