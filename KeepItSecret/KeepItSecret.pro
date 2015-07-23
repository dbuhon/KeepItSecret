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
    client.cpp \
    options.cpp \
    qblowfish.cpp \
    cryptoutils.cpp \
    chatwindow.cpp

HEADERS  += \
    mainwindow.h \
    contactswindow.h \
    newaccountwindow.h \
    newcontactwindow.h \
    client.h \
    options.h \
    qblowfish.h \
    qblowfish_p.h \
    cryptoutils.h \
    chatwindow.h

FORMS    += \
    mainwindow.ui \
    contactswindow.ui \
    newaccountwindow.ui \
    newcontactwindow.ui \
    chatwindow.ui

CONFIG += mobility \
       += c++11

MOBILITY =

RESOURCES += \
    res.qrc

