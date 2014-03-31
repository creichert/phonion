TEMPLATE = subdirs
SUBDIRS = integrator \
          messageapp
CONFIG+=ordered

# Copy torchat to build dir
!equals(PWD, $${OUT_PWD}) {
    copytorchat.commands = $(COPY_DIR) $$PWD/torchat $$OUT_PWD
    first.depends = $(first) copytorchat
    export(first.depends)
    export(copytorchat.commands)
    QMAKE_EXTRA_TARGETS += first copytorchat
}
