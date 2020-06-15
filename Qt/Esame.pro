QT += core
QT += widgets
QT += gui

TARGET = Dynamic_interaction_graph

CONFIG   -= app_bundle
CONFIG += c++11

#CONFIG   += console #Per QDebug()

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

HEADERS += \
    ColorBar.h \
    Controller.h \
    Graph.h \
    MainWindow.h

SOURCES += \
    Graph.cpp \
    main.cpp
