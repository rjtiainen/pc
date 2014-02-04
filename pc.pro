#-------------------------------------------------
#
# Project created by QtCreator 2013-02-19T20:16:34
#
#-------------------------------------------------

QT       += core gui

TARGET = pc
TEMPLATE = app


SOURCES += main.cpp\
        programmerscalculator.cpp \
    calcstack.cpp \
    rpnparser.cpp \
    calcstackitem.cpp

HEADERS  += programmerscalculator.h \
    parser.h \
    calcstack.h \
    rpnparser.h \
    calcstackitem.h

FORMS    += programmerscalculator.ui
