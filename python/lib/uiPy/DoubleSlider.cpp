// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiPy/DoubleSlider.h>

#include <feather-tk/ui/DoubleSlider.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace feather_tk
{
    void doubleSlider(py::module_& m)
    {
        py::class_<DoubleSlider, IWidget, std::shared_ptr<DoubleSlider> >(m, "DoubleSlider")
            .def(
                py::init(py::overload_cast<
                    const std::shared_ptr<Context>&,
                    const std::shared_ptr<IWidget>&>(&DoubleSlider::create)),
                py::arg("context"),
                py::arg("parent") = nullptr)
            .def(
                py::init(py::overload_cast<
                    const std::shared_ptr<Context>&,
                    const std::shared_ptr<DoubleModel>&,
                    const std::shared_ptr<IWidget>&>(&DoubleSlider::create)),
                py::arg("context"),
                py::arg("model"),
                py::arg("parent") = nullptr)
            .def_property("value", &DoubleSlider::getValue, &DoubleSlider::setValue)
            .def("setCallback", &DoubleSlider::setCallback)
            .def_property("range", &DoubleSlider::getRange, &DoubleSlider::setRange)
            .def_property("step", &DoubleSlider::getStep, &DoubleSlider::setStep)
            .def_property("largeStep", &DoubleSlider::getLargeStep, &DoubleSlider::setLargeStep)
            .def("getModel", &DoubleSlider::getModel);
    }
}