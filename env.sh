#!/bin/bash

export PYTHONPATH=$PWD/integrator:$PWD/phonion/torchat/src

# Use this until a build layout has been finalised. Use qmake install targets.
export LD_LIBRARY_PATH=$PWD/integrator:$PWD/mumble/debug
