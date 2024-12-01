// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiPy/Settings.h>

#include <dtk/ui/Settings.h>

#include <dtk/core/Context.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dtk
{
    void settings(py::module_& m)
    {
        m.def(
            "getSettingsPath",
            &getSettingsPath,
            py::arg("directory"),
            py::arg("name"),
            "Get a settings path.");

        py::class_<Settings, ISystem, std::shared_ptr<Settings> >(m, "Settings")
            .def(
                py::init(&Settings::create),
                py::arg("context"),
                py::arg("path"))
            .def("get", &Settings::get, py::arg("key"))
            .def("set", &Settings::set, py::arg("key"), py::arg("value"));
    }
}
