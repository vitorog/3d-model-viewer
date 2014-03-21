#-------------------------------------------------
#
# Project created by QtCreator 2014-02-05T11:49:21
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 3d-model-viewer
TEMPLATE = app

INCLUDEPATH += ../shade-framework
INCLUDEPATH += ../../../glm-0.9.5.2/glm


LIBS += -L/usr/local/lib -lGLU

SOURCES += main.cpp\
        main_window.cpp \
    gl_widget.cpp

HEADERS  += main_window.h \
    gl_widget.h

FORMS    += main_window.ui

unix:!macx: LIBS += -L$$PWD/../Builds/shade-framework-build/ -lshade-framework

INCLUDEPATH += $$PWD/../Builds/shade-framework-build
DEPENDPATH += $$PWD/../Builds/shade-framework-build
