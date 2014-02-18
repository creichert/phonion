include(../phonion.pri)

TEMPLATE = lib
TARGET = phonion

QT += core gui qml quick widgets

HEADERS += app.h \
           appmodel.h \
           buddy.h \
           buddylistmodel.h \
           message.h \
           notification.h \
           notifier.h

SOURCES += appmodel.cpp \
           buddy.cpp \
           buddylistmodel.cpp \
           message.cpp \
           notification.cpp \
           notifier.cpp

RESOURCES += sdk.qrc
