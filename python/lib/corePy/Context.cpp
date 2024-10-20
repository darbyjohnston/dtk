// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <corePy/Context.h>

#include <dtk/core/Context.h>
#include <dtk/core/ISystem.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dtk
{
    void context(py::module_& m)
    {
        py::class_<Context, std::shared_ptr<Context> >(m, "Context")
            .def(py::init(&Context::create))
            .def("addSystem", &Context::addSystem)
            .def_property_readonly("systems", &Context::getSystems)
            .def("getSystemByName", &Context::getSystemByName)
            .def("tick", &Context::tick);
    }
}