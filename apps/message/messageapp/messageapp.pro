include(../../../phonion.pri)
include(../message.pri)

TEMPLATE = lib
TARGET = messageapp

QT += core gui qml quick widgets

INCLUDEPATH += .
INCLUDEPATH += ../integrator
INCLUDEPATH += ../../../sdk

LIBS += -L../integrator -lintegrator -L../../../sdk -lphonion

HEADERS += chatmodel.h \
           messageapp.h

SOURCES += chatmodel.cpp \
           messageapp.cpp

RESOURCES += messageapp.qrc

# RPaths from within the apps/phone/phoneapp/ directory
QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/../integrator
QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/../../../sdk

# RPaths from within the apps/ directory.
QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/message/integrator
QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/../sdk

# Copy to apps dir.
QMAKE_POST_LINK += $$quote($$QMAKE_COPY $${OUT_PWD}/libmessageapp.so $${OUT_PWD}/../../$$escape_expand(\\n\\t))
