#-------------------------------------------------
#
# Project created by QtCreator 2015-05-26T14:34:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testXzing
TEMPLATE = app

CONFIG += C++11

win32:DEFINES += NO_ICONV

INCLUDEPATH += $$PWD/src

SOURCES += main.cpp\
        mainwindow.cpp \
   ImageWrapper.cpp


HEADERS  += mainwindow.h \
    ImageWrapper.h

FORMS    += mainwindow.ui

#win32:!win32-g++: LIBS += -LE:/lib/zxing-cpp/vs2010/ -llibzxing
#else:unix:!macx|win32-g++: LIBS += -LE:/lib/zxing-cpp/mingw/ -lzxing

#INCLUDEPATH += E:/lib/zxing-cpp/src
#DEPENDPATH += E:/lib/zxing-cpp/src

#win32:!win32-g++: PRE_TARGETDEPS += E:/lib/zxing-cpp/vs2010/libzxing.lib
#else:unix:!macx|win32-g++: PRE_TARGETDEPS += E:/lib/zxing-cpp/mingw/libzxing.a

include(E:/lib/zxing-cpp/src/zxing.pri)

MOC_DIR = .moc
OBJECTS_DIR = .obj
