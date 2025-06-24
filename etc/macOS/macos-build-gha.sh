#!/bin/bash

set -x

BUILD_TYPE=$1

mkdir build
cd build
cmake ../etc/SuperBuild \
    -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
    -DCMAKE_INSTALL_PREFIX=$PWD/install \
    -DCMAKE_PREFIX_PATH=$PWD/install \
    -Dfeather_tk_API=$FEATHER_TK_API \
    -Dfeather_tk_nfd=$FEATHER_TK_NFD \
    -Dfeather_tk_PYTHON=$FEATHER_TK_PYTHON \
    -Dfeather_tk_TESTS=$FEATHER_TK_TESTS \
    -Dfeather_tk_EXAMPLES=$FEATHER_TK_EXAMPLES \
    -Dfeather_tk_GCOV=$FEATHER_TK_GCOV \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=${CMAKE_OSX_DEPLOYMENT_TARGET} \
    -DCMAKE_OSX_ARCHITECTURES=${CMAKE_OSX_ARCHITECTURES}
cmake --build . -j 4 --config $BUILD_TYPE

