// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
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

        py::class_<Settings, std::shared_ptr<Settings> >(m, "Settings")
            .def(
                py::init(&Settings::create),
                py::arg("context"),
                py::arg("path"),
                py::arg("reset") = false)
            .def("contains", &Settings::contains, py::arg("key"))
            .def("get", py::overload_cast<const std::string&, bool&>(&Settings::get), py::arg("key"), py::arg("value"))
            .def("get", py::overload_cast<const std::string&, int64_t&>(&Settings::get), py::arg("key"), py::arg("value"))
            .def("get", py::overload_cast<const std::string&, double&>(&Settings::get), py::arg("key"), py::arg("value"))
            .def("get", py::overload_cast<const std::string&, std::string&>(&Settings::get), py::arg("key"), py::arg("value"))
            .def("set", py::overload_cast<const std::string&, bool>(&Settings::set), py::arg("key"), py::arg("value"))
            .def("set", py::overload_cast<const std::string&, int64_t>(&Settings::set), py::arg("key"), py::arg("value"))
            .def("set", py::overload_cast<const std::string&, double>(&Settings::set), py::arg("key"), py::arg("value"))
            .def("set", py::overload_cast<const std::string&, const std::string&>(&Settings::set), py::arg("key"), py::arg("value"));
    }
}
