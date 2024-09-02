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
    namespace core
    {
        void bind(py::module_& m)
        {
            auto sm = m.def_submodule("dtkCore");
            sm.doc() = "Core functionality";

            sm.def("init", &init, "Initialize the library.");

            iSystem(sm);

            box(sm);
            cmdLine(sm);
            color(sm);
            context(sm);
            fontSystem(sm);
            iApp(sm);
            iRender(sm);
            image(sm);
            memory(sm);
            observable(sm);
            observableList(sm);
            observableMap(sm);
            observableValue(sm);
            os(sm);
            random(sm);
            range(sm);
            size(sm);
            vector(sm);
        }
    }
}
