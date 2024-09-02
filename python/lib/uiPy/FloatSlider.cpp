// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiPy/FloatSlider.h>

#include <dtk/ui/FloatSlider.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dtk
{
    void floatSlider(py::module_& m)
    {
        py::class_<FloatSlider, IWidget, std::shared_ptr<FloatSlider> >(m, "FloatSlider")
            .def(
                py::init(&FloatSlider::create),
                py::arg("context"),
                py::arg("model") = nullptr,
                py::arg("parent") = nullptr)
            .def_property("value", &FloatSlider::getValue, &FloatSlider::setValue)
            .def("setCallback", &FloatSlider::setCallback)
            .def_property("range", &FloatSlider::getRange, &FloatSlider::setRange)
            .def_property("step", &FloatSlider::getStep, &FloatSlider::setStep)
            .def_property("largeStep", &FloatSlider::getLargeStep, &FloatSlider::setLargeStep)
            .def("getModel", &FloatSlider::getModel);
    }
}