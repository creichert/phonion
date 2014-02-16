include(../phonion.pri)

TEMPLATE = lib
TARGET = phonion

QT += core gui qml quick widgets

HEADERS += app.h \
           appmodel.h \
           buddy.h \
           message.h \
           notification.h \
           notifier.h

SOURCES += appmodel.cpp \
           buddy.cpp \
           message.cpp \
           notification.cpp \
           notifier.cpp

RESOURCES += sdk.qrc
