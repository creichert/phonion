CONFIG(rpi) {
    SYSROOT = /mnt/rasp-pi-rootfs
}

DEFINES += BOOST_PYTHON_DYNAMIC_LIB
INCLUDEPATH += $$SYSROOT/usr/include $$SYSROOT/usr/include/boost $$SYSROOT/usr/include/python2.7
LIBS += -L$$SYSROOT/usr/local/lib -L$$SYSROOT/usr/lib/python2.7 -lpython2.7 -lboost_python
