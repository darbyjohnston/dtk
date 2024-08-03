[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)
[![Build Status](https://github.com/darbyjohnston/dtk/actions/workflows/ci-workflow.yml/badge.svg)](https://github.com/darbyjohnston/dtk/actions/workflows/ci-workflow.yml)
[![codecov](https://codecov.io/gh/codecov/example-cpp11-cmake/branch/master/graph/badge.svg)](https://codecov.io/gh/darbyjohnston/dtk)

dtk
=======
A toolkit for building DJV and other applications.


Building
========

Building on Linux
-----------------
Clone the repository:
```
git clone https://github.com/darbyjohnston/dtk.git
```
Run CMake:
```
cmake -S dtk/etc/SuperBuild -B Release -DCMAKE_INSTALL_PREFIX=$PWD/Release/install -DCMAKE_PREFIX_PATH=$PWD/Release/install -DCMAKE_BUILD_TYPE=Release
```
Start the build:
```
cmake --build Release -j 4 --config Release
```
Try running the `simple` example:
```
Release/dtk/src/dtk-build/examples/simple/simple
```

Building on macOS
-----------------
Clone the repository:
```
git clone https://github.com/darbyjohnston/dtk.git
```
Run CMake:
```
cmake -S dtk/etc/SuperBuild -B Release -DCMAKE_INSTALL_PREFIX=$PWD/Release/install -DCMAKE_PREFIX_PATH=$PWD/Release/install -DCMAKE_BUILD_TYPE=Release
```
Start the build:
```
cmake --build Release -j 4 --config Release
```
Try running the `simple` example:
```
Release/dtk/src/dtk-build/examples/simple/simple
```

Notes for building on macOS
---------------------------
The CMake variable "CMAKE_OSX_ARCHITECTURES" can be used to specify the build
architecture:
```
-DCMAKE_OSX_ARCHITECTURES=x86_64
```
```
-DCMAKE_OSX_ARCHITECTURES=arm64
```

Building on Windows
-------------------
Clone the repository:
```
git clone https://github.com/darbyjohnston/dtk.git
```
Run CMake:
```
cmake -S dtk\etc\SuperBuild -B Release -DCMAKE_INSTALL_PREFIX=%CD%\Release\install -DCMAKE_PREFIX_PATH=%CD%\Release\install -DCMAKE_BUILD_TYPE=Release
```
Start the build:
```
cmake --build Release -j 4 --config Release
```
Try running the `simple` example:
```
Release\dtk\src\dtk-build\examples\simple\Release\simple
```

