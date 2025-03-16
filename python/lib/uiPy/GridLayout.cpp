// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiPy/GridLayout.h>

#include <dtk/ui/GridLayout.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dtk
{
    void gridLayout(py::module_& m)
    {
        py::class_<GridLayout, IWidget, std::shared_ptr<GridLayout> >(m, "GridLayout")
            .def(
                py::init(&GridLayout::create),
                py::arg("context"),
                py::arg("parent") = nullptr)
            .def(
                "setGridPos",
                &GridLayout::setGridPos,
                py::arg("child"),
                py::arg("row"),
                py::arg("column"))
            .def_property("rowBackgroundRole", &GridLayout::getRowBackgroundRole, &GridLayout::setRowBackgroundRole)
            .def_property("marginRole", &GridLayout::getMarginRole, &GridLayout::setMarginRole)
            .def_property("spacingRole", &GridLayout::getSpacingRole, &GridLayout::setSpacingRole)
            .def("clear", &GridLayout::clear);
    }
}