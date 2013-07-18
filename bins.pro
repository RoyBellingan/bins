#-------------------------------------------------
#
# Project created by QtCreator 2013-05-07T02:03:48
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bins
TEMPLATE = app


SOURCES += main.cpp\
        bins.cpp

HEADERS  += bins.h \
    connection.h \
    tableeditor.h

FORMS    += bins.ui

QMAKE_CXXFLAGS += -std=c++0x
