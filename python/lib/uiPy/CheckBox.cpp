// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiPy/CheckBox.h>

#include <dtk/ui/CheckBox.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dtk
{
    void checkBox(py::module_& m)
    {
        py::class_<CheckBox, IButton, std::shared_ptr<CheckBox> >(m, "CheckBox")
            .def(
                py::init(py::overload_cast<
                    const std::shared_ptr<Context>&,
                    const std::shared_ptr<IWidget>&>(&CheckBox::create)),
                py::arg("context"),
                py::arg("parent") = nullptr)
            .def(
                py::init(py::overload_cast<
                    const std::shared_ptr<Context>&,
                    const std::string&,
                    const std::shared_ptr<IWidget>&>(&CheckBox::create)),
                py::arg("context"),
                py::arg("text"),
                py::arg("parent") = nullptr);
    }
}