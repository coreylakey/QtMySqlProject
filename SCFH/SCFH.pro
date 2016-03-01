#-------------------------------------------------
#
# Project created by QtCreator 2016-01-22T22:53:09
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SCFH
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    demographics.cpp \
    adminreports.cpp \
    gifts.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    demographics.h \
    adminreports.h \
    gifts.h


FORMS    += mainwindow.ui \
    dialog.ui \
    demographics.ui \
    adminreports.ui \
    gifts.ui

