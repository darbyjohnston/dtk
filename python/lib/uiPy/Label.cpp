// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiPy/Label.h>

#include <dtk/ui/Label.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dtk
{
    void label(py::module_& m)
    {
        py::class_<Label, IWidget, std::shared_ptr<Label> >(m, "Label")
            .def(
                py::init(py::overload_cast<
                    const std::shared_ptr<Context>&,
                    const std::shared_ptr<IWidget>&>(&Label::create)),
                py::arg("context"),
                py::arg("parent") = nullptr)
            .def(
                py::init(py::overload_cast<
                    const std::shared_ptr<Context>&,
                    const std::string&,
                    const std::shared_ptr<IWidget>&>(&Label::create)),
                py::arg("context"),
                py::arg("text"),
                py::arg("parent") = nullptr)
            .def_property("text", &Label::getText, &Label::setText)
            .def_property("textRole", &Label::getTextRole, &Label::setTextRole)
            .def_property("marginRole", &Label::getMarginRole, &Label::setMarginRole)
            .def_property("fontRole", &Label::getFontRole, &Label::setFontRole);
    }
}