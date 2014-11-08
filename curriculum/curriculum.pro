#-------------------------------------------------
#
# Project created by QtCreator 2014-11-08T11:49:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = curriculum
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += \
    login.ui

CONFIG += mobility

QMAKE_CXXFLAGS += -std=c++11 -pedantic-errors -O0

MOBILITY = 

RESOURCES += \
    curriculum.qrc

