#-------------------------------------------------
#
# Project created by QtCreator 2021-08-31T16:06:22
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TelnetClient
TEMPLATE = app


win32{
    LIBS     +=-lws2_32
}

SOURCES += main.cpp\
        mainwindow.cpp \
    telnet/qttelnet.cpp

HEADERS  += mainwindow.h \
    telnet/qttelnet.h

FORMS    += mainwindow.ui

INCLUDEPATH += telnet/



