#-------------------------------------------------
#
# Project created by QtCreator 2016-10-02T13:34:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DemPROP
TEMPLATE = app


SOURCES += main.cpp\
        demo.cpp \
    report.cpp \
    spline.cpp \
    objects.cpp \
    fileops.cpp \
    detail.cpp \
    findprop.cpp

HEADERS  += demo.h \
    spline.h \
    report.h \
    objects.h \
    fileops.h \
    detail.h \
    findprop.h

FORMS    += demo.ui \
    report.ui \
    detail.ui \
    findprop.ui

DISTFILES += \
    basics

RC_FILE = ico.rc
