// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiPy/IDialog.h>

#include <dtk/ui/IDialog.h>
#include <dtk/ui/Window.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dtk
{
    void iDialog(py::module_& m)
    {
        py::class_<IDialog, IPopup, std::shared_ptr<IDialog> >(m, "IDialog")
            .def("open", &IDialog::open)
            .def("isOpen", &IDialog::isOpen)
            .def("setCloseCallback", &IDialog::setCloseCallback);
    }
}