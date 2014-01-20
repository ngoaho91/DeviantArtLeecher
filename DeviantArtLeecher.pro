#-------------------------------------------------
#
# Project created by QtCreator 2014-01-17T09:04:23
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DeviantArtLeecher
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    downloadmanager.cpp \
    qtdeviantleecher.cpp

HEADERS  += mainwindow.h \
    downloadmanager.h \
    qtdeviantleecher.h

FORMS    += mainwindow.ui
