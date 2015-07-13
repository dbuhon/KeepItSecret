#-------------------------------------------------
#
# Project created by QtCreator 2015-07-13T13:23:25
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KeepItSecretServer
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
        server.cpp \
        dbtools.cpp \
        kis_user.cpp

HEADERS  += mainwindow.h \
        server.h \
        dbtools.h \
        kis_user.h

FORMS    += mainwindow.ui
