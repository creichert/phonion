TEMPLATE = subdirs
SUBDIRS = integrator \
          messageapp
CONFIG+=ordered

# Copy torchat to build dir
!equals($${PWD}, $${OUT_PWD}) {
    system(cp -r $$PWD/torchat $$OUT_PWD)
}
