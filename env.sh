#!/bin/bash

export PYTHONPATH=$PWD/apps/message/integrator:$PWD/apps/message/torchat/torchat/src

# Use this until a build layout has been finalised. Use qmake install targets.
export LD_LIBRARY_PATH=$PWD/apps/message/integrator:$PWD/apps/phone/mumble/debug:$PWD/sdk

export QT_QPA_EGLFS_PHYSICAL_WIDTH=100
       QT_QPA_EGLFS_PHYSICAL_HEIGHT=100
       QT_QPA_EGLFS_DEPTH=32
