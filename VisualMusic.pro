#-------------------------------------------------
#
# Project created by QtCreator 2018-05-19T16:20:10
#
#-------------------------------------------------

QT       += core gui dbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VisualMusic
TEMPLATE = app
CONFIG += c++11 link_pkgconfig
PKGCONFIG += dtkwidget

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        manframe.cpp \
    qroundprogressbar.cpp \
    mpris/dbusinterface.cpp \
    mpris/dbusmpris.cpp \
    mpris/dmprismonitor.cpp

HEADERS += \
        manframe.h \
    qroundprogressbar.h \
    mpris/dbusinterface.h \
    mpris/dbusmpris.h \
    mpris/dmprismonitor.h

DISTFILES += \
    mpris/org.freedesktop.DBus.xml \
    mpris/org.mpris.MediaPlayer2.xml
