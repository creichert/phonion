include(../phonion.pri)

TEMPLATE = app
TARGET = phonion
INSTALL += phonion

QT += core gui qml quick widgets

CONFIG(voip) {
    DEFINES += "VOIP"
}

INCLUDEPATH += .
INCLUDEPATH += ../integrator
LIBS += -L../integrator -lintegrator

INCLUDEPATH += ../mumble/src
INCLUDEPATH += ../mumble/src/mumble

debug {
    LIBS += -L../mumble/debug -lmumble
}

release {
    LIBS += -L../mumble/release -lmumble
}

HEADERS += applauncher.h \
           messageapp.h \
           buddylistmodel.h \
           chatmodel.h \
           voipclient.h

SOURCES += applauncher.cpp \
           main.cpp \
           messageapp.cpp \
           voipclient.cpp \
           buddylistmodel.cpp \
           chatmodel.cpp

RESOURCES += main.qrc
