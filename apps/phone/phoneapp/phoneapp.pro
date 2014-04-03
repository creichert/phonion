include(../../../phonion.pri)

TEMPLATE = lib
TARGET = phoneapp
DEPENDS = mumbl

QT += gui widgets qml

INCLUDEPATH += ../mumble/src
INCLUDEPATH += ../mumble/src
INCLUDEPATH += ../mumble/src/mumble
INCLUDEPATH += ../../../sdk

# Use this to build Mumble.pb.h out of source.
INCLUDEPATH += $$OUT_PWD/../mumble/src/mumble

LIBS += -L../../../sdk -lphonion

debug {
    LIBS += -L../mumble/debug -lmumble

    # RPath from within the apps/phone/phoneapp/ directory
    QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/../mumble/debug
    # RPath from within the apps/ directory.
    QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/phone/mumble/debug
}
release {
    LIBS += -L../mumble/release -lmumble
    # RPath from within the apps/phone/phoneapp/ directory
    QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/../mumble/release
    # RPath from within the apps/ directory.
    QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/phone/mumble/release
}
QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/../../../sdk

HEADERS += phoneapp.h \
           voipclient.h

SOURCES += phoneapp.cpp \
           voipclient.cpp

RESOURCES += phoneapp.qrc

# Copy to apps dir.
QMAKE_POST_LINK += $$quote($$QMAKE_COPY $${OUT_PWD}/libphoneapp.so $${OUT_PWD}/../../$$escape_expand(\\n\\t))
