// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiPy/DoubleEdit.h>

#include <dtk/ui/DoubleEdit.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dtk
{
    void doubleEdit(py::module_& m)
    {
        py::class_<DoubleEdit, IWidget, std::shared_ptr<DoubleEdit> >(m, "DoubleEdit")
            .def(
                py::init(py::overload_cast<
                    const std::shared_ptr<Context>&,
                    const std::shared_ptr<IWidget>&>(&DoubleEdit::create)),
                py::arg("context"),
                py::arg("parent") = nullptr)
            .def(
                py::init(py::overload_cast<
                    const std::shared_ptr<Context>&,
                    const std::shared_ptr<DoubleModel>&,
                    const std::shared_ptr<IWidget>&>(&DoubleEdit::create)),
                py::arg("context"),
                py::arg("model"),
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