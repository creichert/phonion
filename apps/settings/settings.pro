include(../../phonion.pri)

TEMPLATE = lib
TARGET = settingsapp

QT += core qml

INCLUDEPATH += .
INCLUDEPATH += ../../sdk

LIBS += -L../../sdk -lphonion

HEADERS += settings.h

SOURCES += settings.cpp

RESOURCES += settings.qrc

QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/../../sdk
