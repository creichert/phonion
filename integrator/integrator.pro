TEMPLATE = lib
TARGET = integrator

HEADERS += integrator.h
SOURCES += integrator.cpp

INCLUDEPATH += /usr/include /usr/include/boost /usr/include/python2.7
DEFINES += BOOST_PYTHON_DYNAMIC_LIB
LIBS += -L/usr/local/lib -L/usr/lib/python2.7 -lpython2.7 -lboost_python

