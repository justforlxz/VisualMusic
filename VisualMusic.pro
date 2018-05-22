QT       += core gui dbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VisualMusic
TEMPLATE = app
CONFIG += c++11 link_pkgconfig
PKGCONFIG += dtkwidget

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
