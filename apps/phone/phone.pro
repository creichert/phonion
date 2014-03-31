TEMPLATE = subdirs

# Copy Mumble protocol buffer to build directory.
#
# Copying the proto file is necessary when shadow building.
!equals(PWD, $${OUT_PWD}) {
    copymumbleproto.commands = $(COPY) $$PWD/mumble/src/Mumble.proto $$OUT_PWD/mumble/src/
    first.depends = $(first) copydata
    export(first.depends)
    export(copymumbleproto.commands)
    QMAKE_EXTRA_TARGETS += first copymumbleproto

    copymurmurini.commands = $(COPY) $$PWD/murmur.ini $$OUT_PWD
    first.depends = $(first) copymurmurini
    export(first.depends)
    export(copymurmurini.commands)
    QMAKE_EXTRA_TARGETS += first copymurmurini
}

SUBDIRS = mumble/src/murmur \
          mumble/src/mumble \
          phoneapp
CONFIG += ordered
