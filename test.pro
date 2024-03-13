#-------------------------------------------------
#
# Project created by QtCreator 2024-02-23T15:47:20
#
#-------------------------------------------------

QT       += core gui concurrent
CONFIG += C++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    datamodel.cpp \
    database.cpp

HEADERS  += widget.h \
    datamodel.h \
    database.h

FORMS    += widget.ui
LIBS += -lsqlite3
