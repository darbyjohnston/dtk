// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <corePy/Bindings.h>

#include <corePy/Box.h>
#include <corePy/CmdLine.h>
#include <corePy/Color.h>
#include <corePy/Context.h>
#include <corePy/FontSystem.h>
#include <corePy/IApp.h>
#include <corePy/IRender.h>
#include <corePy/ISystem.h>
#include <corePy/Image.h>
#include <corePy/Memory.h>
#include <corePy/Observable.h>
#include <corePy/ObservableList.h>
#include <corePy/ObservableMap.h>
#include <corePy/ObservableValue.h>
#include <corePy/OS.h>
#include <corePy/Random.h>
#include <corePy/Range.h>
#include <corePy/Size.h>
#include <corePy/Vector.h>

#include <dtk/core/Context.h>
#include <dtk/core/Init.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace dtk
{
    void coreBind(py::module_& m)
    {
        m.def("init", &coreInit, "Initialize the library.");

        iSystem(m);

        box(m);
        cmdLine(m);
        color(m);
        context(m);
        fontSystem(m);
        iApp(m);
        iRender(m);
        image(m);
        memory(m);
        observable(m);
        observableList(m);
        observableMap(m);
        observableValue(m);
        os(m);
        random(m);
        range(m);
        size(m);
        vector(m);
    }
}
