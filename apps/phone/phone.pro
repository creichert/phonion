TEMPLATE = subdirs

# Copy Mumble protocol buffer to build directory.
#
# Copying the proto file is necessary when shadow building.
!equals($${PWD}, $${OUT_PWD}) {
    system(cp $$PWD/mumble/src/Mumble.proto $$OUT_PWD/mumble/src/)
    system($$PWD/murmur.ini $$OUT_PWD)
}

SUBDIRS = mumble/src/murmur \
          mumble/src/mumble \
          phoneapp
CONFIG += ordered
