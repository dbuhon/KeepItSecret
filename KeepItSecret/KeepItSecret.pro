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
    cryptotools.cpp \
    client.cpp \
    options.cpp \
    chatdialog.cpp

HEADERS  += \
    mainwindow.h \
    contactswindow.h \
    newaccountwindow.h \
    newcontactwindow.h \
    cryptotools.h \
    client.h \
    options.h \
    chatdialog.h

FORMS    += \
    mainwindow.ui \
    contactswindow.ui \
    newaccountwindow.ui \
    newcontactwindow.ui \
    chatdialog.ui

CONFIG += mobility \
       += c++11

MOBILITY =

RESOURCES += \
    res.qrc

