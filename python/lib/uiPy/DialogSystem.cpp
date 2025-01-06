// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiPy/DialogSystem.h>

#include <dtk/ui/DialogSystem.h>
#include <dtk/ui/Window.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dtk
{
    void dialogSystem(py::module_& m)
    {
        py::class_<DialogSystem, ISystem, std::shared_ptr<DialogSystem> >(m, "DialogSystem")
            .def(
                py::init(&DialogSystem::create),
                py::arg("context"))
            .def("message",
                &DialogSystem::message,
                py::arg("title"),
                py::arg("text"),
                py::arg("window"))
            .def("confirm",
                &DialogSystem::confirm,
                py::arg("title"),
                py::arg("text"),
                py::arg("window"),
                py::arg("callback"));
    }
}