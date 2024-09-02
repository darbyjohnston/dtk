// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiPy/FloatEdit.h>

#include <dtk/ui/FloatEdit.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dtk
{
    namespace ui
    {
        void floatEdit(py::module_& m)
        {
            py::class_<FloatEdit, IWidget, std::shared_ptr<FloatEdit> >(m, "FloatEdit")
                .def(
                    py::init(&FloatEdit::create),
                    py::arg("context"),
                    py::arg("model") = nullptr,
                    py::arg("parent") = nullptr)
                .def_property("value", &FloatEdit::getValue, &FloatEdit::setValue)
                .def("setCallback", &FloatEdit::setCallback)
                .def_property("range", &FloatEdit::getRange, &FloatEdit::setRange)
                .def_property("step", &FloatEdit::getStep, &FloatEdit::setStep)
                .def_property("largeStep", &FloatEdit::getLargeStep, &FloatEdit::setLargeStep)
                .def("getModel", &FloatEdit::getModel)
                .def_property("precision", &FloatEdit::getPrecision, &FloatEdit::setPrecision)
                .def_property("fontRole", &FloatEdit::getFontRole, &FloatEdit::setFontRole);
        }
    }
}
