TEMPLATE = subdirs

# Copy Mumble protocol buffer to build directory.
#
# Copying the proto file is necessary when shadow building.
!exists($$OUT_PWD/mumble/src/Mumble.proto) {
    copydata.commands = $(COPY) $$PWD/mumble/src/Mumble.proto $$OUT_PWD/mumble/src/
    first.depends = $(first) copydata
    export(first.depends)
    export(copydata.commands)
    QMAKE_EXTRA_TARGETS += first copydata
}

SUBDIRS = mumble/src/murmur \
          mumble/src/mumble \
          phoneapp
CONFIG += ordered
