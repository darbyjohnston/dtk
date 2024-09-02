// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiPy/DoubleSlider.h>

#include <dtk/ui/DoubleSlider.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dtk
{
    namespace ui
    {
        void doubleSlider(py::module_& m)
        {
            py::class_<DoubleSlider, IWidget, std::shared_ptr<DoubleSlider> >(m, "DoubleSlider")
                .def(
                    py::init(&DoubleSlider::create),
                    py::arg("context"),
                    py::arg("model") = nullptr,
                    py::arg("parent") = nullptr)
                .def_property("value", &DoubleSlider::getValue, &DoubleSlider::setValue)
                .def("setCallback", &DoubleSlider::setCallback)
                .def_property("range", &DoubleSlider::getRange, &DoubleSlider::setRange)
                .def_property("step", &DoubleSlider::getStep, &DoubleSlider::setStep)
                .def_property("largeStep", &DoubleSlider::getLargeStep, &DoubleSlider::setLargeStep)
                .def("getModel", &DoubleSlider::getModel);
        }
    }
}
