#-------------------------------------------------
#
# Project created by QtCreator 2015-05-17T20:53:00
#
#-------------------------------------------------

QT       += core gui widgets sql network

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = KeepItSecret
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    contactswindow.cpp \
    newaccountwindow.cpp \
    newcontactwindow.cpp \
    discussionwindow.cpp \
    cryptotools.cpp \
    kis_user.cpp \
    client.cpp \
    options.cpp

HEADERS  += \
    mainwindow.h \
    contactswindow.h \
    newaccountwindow.h \
    newcontactwindow.h \
    discussionwindow.h \
    cryptotools.h \
    kis_user.h \
    client.h \
    options.h

FORMS    += \
    mainwindow.ui \
    contactswindow.ui \
    newaccountwindow.ui \
    newcontactwindow.ui \
    discussionwindow.ui \
    chat.ui

CONFIG += mobility \
       += c++11

MOBILITY =

RESOURCES += \
    res.qrc

