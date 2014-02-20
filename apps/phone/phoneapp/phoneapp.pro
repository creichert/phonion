include(../../../phonion.pri)

TEMPLATE = lib
TARGET = phoneapp
DEPENDS = mumbl

QT += gui widgets qml

CONFIG(voip) {
    DEFINES += "VOIP"
}

INCLUDEPATH += ../mumble/src
INCLUDEPATH += ../mumble/src/mumble
INCLUDEPATH += ../../../sdk

LIBS += -L../../../sdk -lphonion

debug {
    LIBS += -L../mumble/debug -lmumble
    QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/../mumble/debug
}

release {
    LIBS += -L../mumble/release -lmumble
    QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/../mumble/release
}
QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/../../../sdk

HEADERS += phoneapp.h \
           voipclient.h

SOURCES += phoneapp.cpp \
           voipclient.cpp

RESOURCES += phoneapp.qrc
