TEMPLATE = subdirs
SUBDIRS = integrator \
          messageapp
CONFIG+=ordered

# Copy torchat to build dir
!exists($$OUT_PWD/torchat) {
    copydata.commands = $(COPY_DIR) $$PWD/torchat $$OUT_PWD
    first.depends = $(first) copydata
    export(first.depends)
    export(copydata.commands)
    QMAKE_EXTRA_TARGETS += first copydata
}
