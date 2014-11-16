#-------------------------------------------------
#
# Project created by QtCreator 2014-11-08T11:49:09
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = curriculum
TEMPLATE = app


SOURCES += main.cpp\
    cookies/cookies.cpp \
    widget/widget.cpp \
    course_db/course_db.cpp \
    html_parser/html_parser.cpp

HEADERS  += cookies/cookies.h \
    widget/widget.h \
    test/test.h \
    course_db/course_db.h \
    html_parser/html_parser.h

FORMS    += \
    ui/course_table.ui \
    ui/login.ui

CONFIG += mobility

QMAKE_CXXFLAGS += -std=c++11 -pedantic-errors -O0

MOBILITY = 

RESOURCES += \
    curriculum.qrc

OTHER_FILES +=

