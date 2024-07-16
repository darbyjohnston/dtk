#!/bin/bash

set -x

BUILD_TYPE=$1

mkdir build
cd build
cmake ../etc/SuperBuild \
    -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
    -DCMAKE_INSTALL_PREFIX=$PWD/install \
    -DCMAKE_PREFIX_PATH=$PWD/install \
    -Ddtk_API=$DTK_API \
    -Ddtk_NFD=$DTK_NFD \
    -Ddtk_PYTHON=$DTK_PYTHON \
    -Ddtk_TESTS=$DTK_TESTS \
    -Ddtk_EXAMPLES=$DTK_EXAMPLES \
    -Ddtk_GCOV=$DTK_GCOV \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=${CMAKE_OSX_DEPLOYMENT_TARGET} \
    -DCMAKE_OSX_ARCHITECTURES=${CMAKE_OSX_ARCHITECTURES}
cmake --build . -j 4 --config $BUILD_TYPE

