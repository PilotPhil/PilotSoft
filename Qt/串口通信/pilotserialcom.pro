#-------------------------------------------------
#
# Project created by QtCreator 2020-06-05T13:56:07
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT       += charts
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pilotserialcom
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        serial.cpp \
    serialsetting_ui.cpp \
    serialsetting_thread.cpp \
    mychart.cpp

HEADERS += \
        serial.h \
    serialsetting_ui.h \
    serialsetting_thread.h \
    mychart.h

FORMS += \
        serial.ui \
    serialsetting_ui.ui \
    mychart.ui



RESOURCES += \
    pic.qrc
