// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiPy/ProgressDialog.h>

#include <dtk/ui/ProgressDialog.h>
#include <dtk/ui/Window.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dtk
{
    void progressDialog(py::module_& m)
    {
        py::class_<ProgressDialog, IDialog, std::shared_ptr<ProgressDialog> >(m, "ProgressDialog")
            .def(
                py::init(&ProgressDialog::create),
                py::arg("context"),
                py::arg("title"),
                py::arg("text"),
                py::arg("parent") = nullptr)
            .def("setCancelCallback", &ProgressDialog::setCancelCallback);
    }
}