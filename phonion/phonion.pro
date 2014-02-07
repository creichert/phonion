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
           buddy.h \
           buddylistmodel.h \
           chatmodel.h \
           voipclient.h \
           qappphonion.h \
           notifier.h \
           message.h

SOURCES += main.cpp \
           messageapp.cpp \
           voipclient.cpp \
           buddy.cpp \
           buddylistmodel.cpp \
           chatmodel.cpp \
           qappphonion.cpp \
           notifier.cpp \
           message.cpp

RESOURCES += phonion.qrc
