#-------------------------------------------------
#
# Project created by QtCreator 2014-02-05T11:49:21
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 3d-model-viewer
TEMPLATE = app

INCLUDEPATH += /home/vitor/glm/glm-0.9.4.3

SOURCES += main.cpp\
        main_window.cpp \
    model.cpp \
    material.cpp \
    utils.cpp \
    gl_widget.cpp

HEADERS  += main_window.h \
    model.h \
    material.h \
    utils.h \
    gl_widget.h

FORMS    += main_window.ui
