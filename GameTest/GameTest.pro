QT       += testlib

QT       -= gui

TARGET = tst_gametest.cpp
CONFIG   += console
CONFIG   -= app_bundle

CONFIG += C++11

SOURCES +=  tst_gametest.cpp \
            ../Game/statistics.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../Game/statistics.h

INCLUDEPATH += ../Game
DEPENDPATH  += ../Game

