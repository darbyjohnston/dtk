// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiPy/MessageDialog.h>

#include <feather-tk/ui/MessageDialog.h>
#include <feather-tk/ui/Window.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace feather_tk
{
    void messageDialog(py::module_& m)
    {
        py::class_<MessageDialog, IDialog, std::shared_ptr<MessageDialog> >(m, "MessageDialog")
            .def(
                py::init(&MessageDialog::create),
                py::arg("context"),
                py::arg("title"),
                py::arg("text"),
                py::arg("parent") = nullptr)
            .def("setCallback", &MessageDialog::setCallback);
    }
}