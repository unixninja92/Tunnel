# Copyright 2013 unixninja92
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#
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
    movingpolygons.cpp \
    polygonarray.cpp

HEADERS  += tunnelw.h \
    movingpolygons.h \
    polygonarray.h

FORMS    += tunnelw.ui
