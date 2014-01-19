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

HEADERS += messageapp.h \
           buddylistmodel.h \
           chatmodel.h \
           voipclient.h \
           qappphonion.h \
           message.h

SOURCES += main.cpp \
           messageapp.cpp \
           voipclient.cpp \
           buddylistmodel.cpp \
           chatmodel.cpp \
           qappphonion.cpp \
           message.cpp

RESOURCES += main.qrc
