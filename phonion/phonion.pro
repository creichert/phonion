TEMPLATE = app
TARGET = phonion
INSTALL += phonion

QT += core gui qml quick

INCLUDEPATH += .
INCLUDEPATH += ../integrator
LIBS += -L../integrator -lintegrator

# Boost Python
INCLUDEPATH += /usr/include/boost /usr/include/python2.7
LIBS += -L/usr/local/lib -L/usr/lib/python2.7 -lpython2.7 -lboost_python

INCLUDEPATH += ../mumble/src
INCLUDEPATH += ../mumble/src/mumble
LIBS += -L../mumble/debug -lmumble

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
