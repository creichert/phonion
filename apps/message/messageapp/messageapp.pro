include(../../../phonion.pri)
include(../message.pri)

TEMPLATE = lib
TARGET = messageapp

QT += core gui qml quick widgets

INCLUDEPATH += .
INCLUDEPATH += ../integrator
INCLUDEPATH += ../../../sdk

LIBS += -L../integrator -lintegrator -L../../../sdk -lphonion

HEADERS += chatmodel.h \
           messageapp.h

SOURCES += chatmodel.cpp \
           messageapp.cpp

RESOURCES += messageapp.qrc
