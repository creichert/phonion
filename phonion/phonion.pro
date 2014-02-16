include(../phonion.pri)

TEMPLATE = app
TARGET = phonion
INSTALL += phonion

QT += core gui qml quick widgets

INCLUDEPATH += .
INCLUDEPATH += ../sdk

LIBS += -L../sdk -lphonion

HEADERS += phonion.h \

SOURCES += main.cpp \
           phonion.cpp \

RESOURCES += phonion.qrc
