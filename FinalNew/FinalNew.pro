#-------------------------------------------------
#
# Project created by QtCreator 2018-12-04T12:45:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FinalNew
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    mypainter.cpp \
    shape.cpp \
    line.cpp \
    linecontrol.cpp \
    shapecontrol.cpp \
    circle.cpp \
    circlecontrol.cpp \
    ellipse.cpp \
    ellipsecontrol.cpp \
    rectange.cpp \
    rectcontrol.cpp \
    polygon.cpp \
    polygoncontrol.cpp \
    selectwindow.cpp \
    swcontrol.cpp

HEADERS += \
        mainwindow.h \
    mypainter.h \
    shape.h \
    line.h \
    linecontrol.h \
    shapecontrol.h \
    circle.h \
    circlecontrol.h \
    ellipse.h \
    ellipsecontrol.h \
    rectange.h \
    rectcontrol.h \
    polygon.h \
    polygoncontrol.h \
    selectwindow.h \
    swcontrol.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    icon.qrc
