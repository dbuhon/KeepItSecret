#-------------------------------------------------
#
# Project created by QtCreator 2015-05-17T20:53:00
#
#-------------------------------------------------

QT       += core gui bluetooth widgets sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KeepItSecret
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    contactswindow.cpp \
    newaccountwindow.cpp \
    newcontactwindow.cpp \
    deviceselectionwindow.cpp \
    discussionwindow.cpp \
    cryptotools.cpp \
    dbtools.cpp \
    kis_user.cpp \
    client.cpp

HEADERS  += \
    mainwindow.h \
    contactswindow.h \
    newaccountwindow.h \
    newcontactwindow.h \
    deviceselectionwindow.h \
    discussionwindow.h \
    cryptotools.h \
    dbtools.h \
    kis_user.h \
    client.h

FORMS    += \
    mainwindow.ui \
    contactswindow.ui \
    newaccountwindow.ui \
    newcontactwindow.ui \
    deviceselectionwindow.ui \
    discussionwindow.ui \
    chat.ui

CONFIG += mobility \
       += c++11

MOBILITY =

