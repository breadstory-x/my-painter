#-------------------------------------------------
#
# Project created by QtCreator 2018-10-22T22:04:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FinalProject
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
    circle.cpp \
    ellipse.cpp \
    polygon.cpp \
    rectangle.cpp \
    vrect.cpp \
    helpdialog.cpp

HEADERS += \
        mainwindow.h \
    mypainter.h \
    shape.h \
    line.h \
    circle.h \
    ellipse.h \
    polygon.h \
    rectangle.h \
    vrect.h \
    helpdialog.h

FORMS += \
        mainwindow.ui \
    helpdialog.ui

RESOURCES += \
    icon.qrc

DISTFILES += \
    ../icons/×.bmp \
    ../icons/√.bmp \
    ../icons/保存.bmp \
    ../icons/裁剪.bmp \
    ../icons/打开.bmp \
    ../icons/多边形.bmp \
    ../icons/矩形.bmp \
    ../icons/矩形选择框.bmp \
    ../icons/铅笔.bmp \
    ../icons/曲线.bmp \
    ../icons/提示.bmp \
    ../icons/退出.bmp \
    ../icons/椭圆.bmp \
    ../icons/橡皮.bmp \
    ../icons/新建.bmp \
    ../icons/颜料桶.bmp \
    ../icons/颜色.bmp \
    ../icons/圆.bmp \
    ../icons/直线.bmp
