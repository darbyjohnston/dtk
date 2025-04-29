[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)
[![Build Status](https://github.com/darbyjohnston/dtk/actions/workflows/ci-workflow.yml/badge.svg)](https://github.com/darbyjohnston/dtk/actions/workflows/ci-workflow.yml)
[![codecov](https://codecov.io/gh/codecov/example-cpp11-cmake/branch/master/graph/badge.svg)](https://codecov.io/gh/darbyjohnston/dtk)

dtk
===
dtk is a C++ library for building lightweight cross-platform applications.

Features:
* Support for Linux, macOS, and Windows
* Widgets including buttons, editors, sliders, and menus
* Layouts including horizontal, vertical, grid, and tabs
* Keyboard navigation
* Command-line parsing
* WIP Python bindings
* Entire project and dependencies builds in a few minutes
* Staticly linked demo binaries are under 10MB

Todo:
* Multiple line text editor widget
* Complete Python bindings

Projects that use dtk:
* https://github.com/darbyjohnston/tlRender
* https://github.com/OpenTimelineIO/toucan

Demo example with dark color style:

![DemoDarkStyle](etc/Images/DemoDarkStyle.png)

Demo example with light color style:

![DemoLightStyle](etc/Images/DemoLightStyle.png)

Simple C++ example that shows a window with a text label:
```
#include <dtk/ui/App.h>
#include <dtk/ui/Label.h>
#include <dtk/ui/MainWindow.h>

using namespace dtk;

int main(int argc, char** argv)
{
    auto context = Context::create();
    auto args = convert(argc, argv);
    auto app = App::create(context, args, "simple", "Simple example");
    if (app->getExit() != 0)
        return app->getExit();

    auto window = MainWindow::create(context, app, "simple", Size2I(1280, 960));
    app->addWindow(window);

    auto label = Label::create(context, "Hello world");
    label->setAlign(HAlign::Center, VAlign::Center);
    label->setStretch(Stretch::Expanding);
    window->setWidget(label);

    window->show();
    app->run();
    return 0;
}
```

Simple Python exmple that shows a window with a text label:
```
import dtk
import sys
    
context = dtk.Context()
app = dtk.App(context, sys.argv, "simple", "Simple example")
if app.getExit() != 0:
    sys.exit(app.getExit())

window = dtk.MainWindow(context, app, "simple", dtk.Size2I(1280, 960))
app.addWindow(window)

label = dtk.Label(context, "Hello world")
label.setAlign(dtk.HAlign.Center, dtk.VAlign.Center);
label.setStretch(dtk.Stretch.Expanding);
window.setWidget(label)

window.show()
app.run()
# \bug Need to manually reset the window.
window = None

```


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

