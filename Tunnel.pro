
#-------------------------------------------------
#
# Project created by QtCreator 2013-09-12T02:23:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tunnel
TEMPLATE = app


SOURCES += main.cpp\
        tunnelw.cpp \
    score.cpp \
    movingpolygons.cpp \
    dot.cpp \
    endscreen.cpp

HEADERS  += tunnelw.h \
    score.h \
    movingpolygons.h \
    dot.h \
    shared.h \
    endscreen.h

FORMS    += tunnelw.ui
