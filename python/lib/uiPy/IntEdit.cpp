// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiPy/IntEdit.h>

#include <dtk/ui/IntEdit.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dtk
{
    void intEdit(py::module_& m)
    {
        py::class_<IntEdit, IWidget, std::shared_ptr<IntEdit> >(m, "IntEdit")
            .def(
                py::init(&IntEdit::create),
                py::arg("context"),
                py::arg("model") = nullptr,
                py::arg("parent") = nullptr)
            .def_property("value", &IntEdit::getValue, &IntEdit::setValue)
            .def("setCallback", &IntEdit::setCallback)
            .def_property("range", &IntEdit::getRange, &IntEdit::setRange)
            .def_property("step", &IntEdit::getStep, &IntEdit::setStep)
            .def_property("largeStep", &IntEdit::getLargeStep, &IntEdit::setLargeStep)
            .def("getModel", &IntEdit::getModel)
            .def_property("fontRole", &IntEdit::getFontRole, &IntEdit::setFontRole);
    }
}