// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkCorePy/Bindings.h>

#include <dtkCorePy/Box.h>
#include <dtkCorePy/Color.h>
#include <dtkCorePy/Context.h>
#include <dtkCorePy/FontSystem.h>
#include <dtkCorePy/IRender.h>
#include <dtkCorePy/ISystem.h>
#include <dtkCorePy/Image.h>
#include <dtkCorePy/Memory.h>
#include <dtkCorePy/Observable.h>
#include <dtkCorePy/ObservableList.h>
#include <dtkCorePy/ObservableMap.h>
#include <dtkCorePy/ObservableValue.h>
#include <dtkCorePy/OS.h>
#include <dtkCorePy/Random.h>
#include <dtkCorePy/Range.h>
#include <dtkCorePy/Size.h>
#include <dtkCorePy/Vector.h>

#include <dtkCore/Context.h>
#include <dtkCore/Init.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace dtk
{
    namespace core
    {
        void bind(py::module_& m)
        {
            auto sm = m.def_submodule("tgCore");
            sm.doc() = "Core functionality";

            sm.def("init", &init, "Initialize the library.");

            iSystem(sm);

            box(sm);
            color(sm);
            context(sm);
            fontSystem(sm);
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
