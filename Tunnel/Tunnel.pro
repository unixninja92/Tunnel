
#-------------------------------------------------
#
# Project created by QtCreator 2013-09-12T02:23:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = Tunnel
TEMPLATE = app


SOURCES += main.cpp\
        tunnelw.cpp \
    score.cpp \
    movingpolygons.cpp \
    dot.cpp \
    endscreen.cpp \
    mainmenu.cpp

HEADERS  += tunnelw.h \
    score.h \
    movingpolygons.h \
    dot.h \
    shared.h \
    endscreen.h \
    mainmenu.h

FORMS    += tunnelw.ui \
    mainmenu.ui

DISTFILES += \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/AndroidManifest.xml \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
