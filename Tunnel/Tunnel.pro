
#-------------------------------------------------
#
# Project created by QtCreator 2013-09-12T02:23:10
#
#-------------------------------------------------

QT       += core gui widgets concurrent

TARGET = build/Tunnel
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
        tunnelw.cpp \
    score.cpp \
    movingpolygons.cpp \
    endscreen.cpp \
    mainmenu.cpp

HEADERS  += tunnelw.h \
    score.h \
    movingpolygons.h \
    shared.h \
    endscreen.h \
    mainmenu.h

FORMS    += tunnelw.ui \
    mainmenu.ui

#DISTFILES += \
#    android/gradle/wrapper/gradle-wrapper.jar \
#    android/AndroidManifest.xml \
#    android/res/values/libs.xml \
#    android/build.gradle \
#    android/gradle/wrapper/gradle-wrapper.properties \
#    android/gradlew \
#    android/gradlew.bat

#macx {
#QMAKE_MAC_SDK = macosx10.11
#}

#ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
