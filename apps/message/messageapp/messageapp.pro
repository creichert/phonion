include(../message.pri)

TEMPLATE = lib
TARGET = messageapp

QT += core gui qml quick widgets

INCLUDEPATH += .
INCLUDEPATH += ../integrator
INCLUDEPATH += ../../../sdk

LIBS += -L../integrator -lintegrator -L../../../sdk -lphonion

HEADERS += buddylistmodel.h \
           chatmodel.h \
           messageapp.h

SOURCES += buddylistmodel.cpp \
           messageapp.cpp \
           chatmodel.cpp

RESOURCES += messageapp.qrc
