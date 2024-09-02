// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiPy/IntEditSlider.h>

#include <dtk/ui/IntEditSlider.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dtk
{
    void intEditSlider(py::module_& m)
    {
        py::class_<IntEditSlider, IWidget, std::shared_ptr<IntEditSlider> >(m, "IntEditSlider")
            .def(
                py::init(&IntEditSlider::create),
                py::arg("context"),
                py::arg("model") = nullptr,
                py::arg("parent") = nullptr)
            .def_property("value", &IntEditSlider::getValue, &IntEditSlider::setValue)
            .def("setCallback", &IntEditSlider::setCallback)
            .def_property("range", &IntEditSlider::getRange, &IntEditSlider::setRange)
            .def_property("step", &IntEditSlider::getStep, &IntEditSlider::setStep)
            .def_property("largeStep", &IntEditSlider::getLargeStep, &IntEditSlider::setLargeStep)
            .def_property("defaultValue", &IntEditSlider::getDefaultValue, &IntEditSlider::setDefaultValue)
            .def("getModel", &IntEditSlider::getModel)
            .def_property("fontRole", &IntEditSlider::getFontRole, &IntEditSlider::setFontRole);
    }
}