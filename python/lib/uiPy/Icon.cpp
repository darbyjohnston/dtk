// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiPy/Icon.h>

#include <dtk/ui/Icon.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dtk
{
    void icon(py::module_& m)
    {
        py::class_<Icon, IWidget, std::shared_ptr<Icon> >(m, "Icon")
            .def(
                py::init(py::overload_cast<
                    const std::shared_ptr<Context>&,
                    const std::shared_ptr<IWidget>&>(&Icon::create)),
                py::arg("context"),
                py::arg("parent") = nullptr)
            .def(
                py::init(py::overload_cast<
                    const std::shared_ptr<Context>&,
                    const std::string&,
                    const std::shared_ptr<IWidget>&>(&Icon::create)),
                py::arg("context"),
                py::arg("icon"),
                py::arg("parent") = nullptr)
        .def_property("icon", &Icon::getIcon, &Icon::setIcon)
        .def_property("marginRole", &Icon::getMarginRole, &Icon::setMarginRole);
    }
}
