TEMPLATE = subdirs

# Copy Mumble protocol buffer to build directory.
#
# Copying the proto file is necessary when shadow building.
!equals($${PWD}, $${OUT_PWD}) {
    copymurmurini.commands = $(COPY) $$PWD/murmur.ini $$OUT_PWD
    copymurmurini.command += $(COPY) $$PWD/mumble/src/Mumble.proto $$OUT_PWD/mumble/src/
    first.depends = $(first) copymurmurini
    export(first.depends)
    export(copymurmurini.commands)
    QMAKE_EXTRA_TARGETS += first copymurmurini
}

SUBDIRS = mumble/src/murmur \
          mumble/src/mumble \
          phoneapp
CONFIG += ordered
