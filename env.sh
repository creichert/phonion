#!/bin/bash

export QT_QPA_EGLFS_PHYSICAL_WIDTH=100
       QT_QPA_EGLFS_PHYSICAL_HEIGHT=100
       QT_QPA_EGLFS_DEPTH=32

# TODO: Change the name of this file to configure and do this.
git submodule update --init
cd apps/phone/mumble
git submodule update --init
cd ../../..

# Read cmd line args for more CONFIG options
qmake CONFIG+=phonion CONFIG+=voip -recursive
