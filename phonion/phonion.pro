TEMPLATE = app
TARGET = phonion
INCLUDEPATH += .

INCLUDEPATH += /usr/include/boost /usr/include/python2.7
LIBS += -L/usr/local/lib -L/usr/lib/python2.7 -lpython2.7 -lboost_python

# Boost Python
QT += core gui qml quick

INCLUDEPATH += ../integrator

HEADERS += applauncher.h \
           messageapp.h \
           buddylistmodel.h \
           chatmodel.h \
           ../integrator/integrator.h \

SOURCES += applauncher.cpp \
           main.cpp \
           messageapp.cpp \
           buddylistmodel.cpp \
           chatmodel.cpp

RESOURCES += main.qrc
