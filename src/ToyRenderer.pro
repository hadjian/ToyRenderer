#-------------------------------------------------
#
# Project created by QtCreator 2013-02-03T14:13:45
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = ToyRenderer
TEMPLATE = app

INCLUDEPATH += ../../ToyMatrix/ToyMatrix


SOURCES += main.cpp\
    toyglwidget.cpp \
    toymainwindow.cpp \
    toyrenderengine.cpp

HEADERS  += \
    toyglwidget.h \
    toymainwindow.h \
    toyrenderengine.h

FORMS    += mainwindow.ui
