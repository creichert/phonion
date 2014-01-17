#!/bin/bash

export PYTHONPATH=$PWD/integrator:$PWD/phonion/torchat/src

# Use this until a build layout has been finalised. Use qmake install targets.
export LD_LIBRARY_PATH=$PWD/integrator:$PWD/mumble/debug

export QT_QPA_EGLFS_PHYSICAL_WIDTH=100
       QT_QPA_EGLFS_PHYSICAL_HEIGHT=100
       QT_QPA_EGLFS_DEPTH=32
