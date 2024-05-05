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

# Добавьте путь к конфигурационному файлу Doxygen
DOXYGEN_CONFIG = Doxyfile

# Проверьте, установлен ли Doxygen, и определите цель для Makefile
system(doxygen -v) {
    doxy.target = doxygen
    doxy.commands = doxygen $$DOXYGEN_CONFIG
    doxy.depends = FORCE

    QMAKE_EXTRA_TARGETS += doxy
    QMAKE_CLEAN += docs/*
}

# Дополнительно можно создать файл Doxyfile автоматически, если его нет
!exists($$DOXYGEN_CONFIG) {
    system(doxygen -g $$DOXYGEN_CONFIG)
}
