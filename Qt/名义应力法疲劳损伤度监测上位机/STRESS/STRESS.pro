#-------------------------------------------------
#
# Project created by QtCreator 2020-03-26T13:40:11
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = STRESS
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        stress.cpp \
    COM/serial_ui.cpp \
    COM/serialread_thread.cpp \
    ALGORITHM/algorithm_ui.cpp \
    ALGORITHM/algorithm_thread.cpp \
    UserInterface/linechart_ui.cpp \
    UserInterface/table_ui.cpp

HEADERS  += stress.h \
    COM/serial_ui.h \
    COM/serialread_thread.h \
    ALGORITHM/algorithm_ui.h \
    ALGORITHM/algorithm_thread.h \
    UserInterface/linechart_ui.h \
    UserInterface/table_ui.h

FORMS    += stress.ui \
    COM/serial_ui.ui \
    ALGORITHM/algorithm_ui.ui \
    UserInterface/linechart_ui.ui \
    UserInterface/table_ui.ui

RESOURCES += \
    1.qrc
