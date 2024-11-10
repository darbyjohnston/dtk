// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiPy/IconSystem.h>

#include <dtk/ui/IconSystem.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dtk
{
    void iconSystem(py::module_& m)
    {
        py::class_<IconSystem, ISystem, std::shared_ptr<IconSystem> >(m, "IconSystem")
            .def(
                py::init(&IconSystem::create),
                py::arg("context"))
            .def_property_readonly("names", &IconSystem::getNames);
    }
}
