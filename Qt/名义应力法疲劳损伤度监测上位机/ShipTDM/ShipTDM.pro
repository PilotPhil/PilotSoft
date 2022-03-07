#-------------------------------------------------
#
# Project created by QtCreator 2020-03-14T08:28:38
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShipTDM
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
        shiptdm.cpp \
    dynamiccurve.cpp \
    transferdata.cpp \
    QRainFlow/rf_thread.cpp \
    myt_serialreadonly.cpp \
    serialcom.cpp \
    damagecount.cpp

HEADERS  += shiptdm.h \
    dynamiccurve.h \
    transferdata.h \
    QRainFlow/rf_thread.h \
    myt_serialreadonly.h \
    serialcom.h \
    damagecount.h

FORMS    += shiptdm.ui \
    dynamiccurve.ui \
    transferdata.ui \
    serialcom.ui \
    damagecount.ui

RESOURCES += \
    icon.qrc
