TEMPLATE = app
TARGET = phonion
INCLUDEPATH += .

INCLUDEPATH += /usr/include/boost /usr/include/python2.7
DEFINES += BOOST_PYTHON_DYNAMIC_LIB
LIBS += -L/usr/local/lib -L/usr/lib/python2.7 -lpython2.7 -lboost_python

# Boost Python
QT += core gui qml quick

INCLUDEPATH += ../integrator

HEADERS += applauncher.h \
           messageapp.h \
           ../integrator/integrator.h

SOURCES += applauncher.cpp \
           main.cpp \
           messageapp.cpp

RESOURCES += main.qrc
