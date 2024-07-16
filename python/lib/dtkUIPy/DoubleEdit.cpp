// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkUIPy/DoubleEdit.h>

#include <dtkUI/DoubleEdit.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dtk
{
    namespace ui
    {
        void doubleEdit(py::module_& m)
        {
            py::class_<DoubleEdit, IWidget, std::shared_ptr<DoubleEdit> >(m, "DoubleEdit")
                .def(
                    py::init(&DoubleEdit::create),
                    py::arg("context"),
                    py::arg("model") = nullptr,
                    py::arg("parent") = nullptr)
                .def_property("value", &DoubleEdit::getValue, &DoubleEdit::setValue)
                .def("setCallback", &DoubleEdit::setCallback)
                .def_property("range", &DoubleEdit::getRange, &DoubleEdit::setRange)
                .def_property("step", &DoubleEdit::getStep, &DoubleEdit::setStep)
                .def_property("largeStep", &DoubleEdit::getLargeStep, &DoubleEdit::setLargeStep)
                .def("getModel", &DoubleEdit::getModel)
                .def_property("precision", &DoubleEdit::getPrecision, &DoubleEdit::setPrecision)
                .def_property("fontRole", &DoubleEdit::getFontRole, &DoubleEdit::setFontRole);
        }
    }
}
