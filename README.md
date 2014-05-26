# Phonion: Secure Communications Framework

Phonion is an experimental VOIP and messaging framework which uses Tor Hidden
Services.

Phonion uses QML and provides a lightweight plugin sandbox for writing
extensions.

## Dependendencies

    # Qt deps
    $ sudo apt-get install libxcb1 libxcb1-dev libx11-xcb1 libx11-xcb-dev \
                   libxcb-keysyms1 libxcb-keysyms1-dev libxcb-image0 libxcb-image0-dev libxcb-shm0 \
                   libxcb-shm0-dev libxcb-icccm4 libxcb-icccm4-dev libxcb-sync0 libxcb-sync0-dev \
                   libxcb-render-util0 libxcb-render-util0-dev libxcb-xfixes0-dev libxrender-dev \
                   libxcb-shape0-dev libxcb-randr0-dev libxcb-glx0-dev

    $ sudo apt-get install libxkbcommon-dev libudev-dev libwayland-dev libpng12-dev \
                   libjpeg8-dev libmtdev-dev autotools-dev autoconf automake bison flex \
                   libasound2-dev libxext-dev x11proto-xext-dev libxcursor-dev libxfixes-dev \
                   x11proto-fixes-dev libffi-dev libsm-dev libxcomposite-dev

    # Install Tortalk deps
    sudo apt-get install libboost-python

    # Install Mumble deps
    sudo apt-get install build-essential pkg-config qt4-dev-tools libqt4-dev libspeex1 \
              libspeex-dev libboost-dev libasound2-dev libssl-dev g++ \
              libspeechd-dev libzeroc-ice-dev ice-slice libpulse-dev slice2cpp \
              libcap-dev libspeexdsp-dev libprotobuf-dev protobuf-compiler \
              libogg-dev libavahi-compat-libdnssd-dev libsndfile1-dev \
              libg15daemon-client-dev libxi-dev libopus-dev libcelt0-0 libcelt-dev
## Build

    $ ./configure
    $ mkdir build && cd build/
    $ qmake CONFIG+=phonion CONFIG+=debug -recursive ..
    $ make

## Security

* Test for DNS Leaks

    tcpdump -vvvv -i <your_device> dst port 64738
