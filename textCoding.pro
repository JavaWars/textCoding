#-------------------------------------------------
#
# Project created by QtCreator 2016-11-16T13:21:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = textCoding
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    formcezar.cpp \
    formenigma.cpp \
    formwithpublickey.cpp \
    shifr.cpp \
    rsa.cpp \
    enigma.cpp

HEADERS  += mainwindow.h \
    formcezar.h \
    formenigma.h \
    formwithpublickey.h \
    shifr.h \
    rsa.h \
    enigma.h

FORMS    += mainwindow.ui \
    formcezar.ui \
    formenigma.ui \
    formwithpublickey.ui

RESOURCES += \
    res.qrc

RC_ICONS = cezar.ico
