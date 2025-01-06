// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiPy/DoubleEditSlider.h>

#include <dtk/ui/DoubleEditSlider.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dtk
{
    void doubleEditSlider(py::module_& m)
    {
        py::class_<DoubleEditSlider, IWidget, std::shared_ptr<DoubleEditSlider> >(m, "DoubleEditSlider")
            .def(
                py::init(py::overload_cast<
                    const std::shared_ptr<Context>&,
                    const std::shared_ptr<IWidget>&>(&DoubleEditSlider::create)),
                py::arg("context"),
                py::arg("parent") = nullptr)
            .def(
                py::init(py::overload_cast<
                    const std::shared_ptr<Context>&,
                    const std::shared_ptr<DoubleModel>&,
                    const std::shared_ptr<IWidget>&>(&DoubleEditSlider::create)),
                py::arg("context"),
                py::arg("model"),
                py::arg("parent") = nullptr)
            .def_property("value", &DoubleEditSlider::getValue, &DoubleEditSlider::setValue)
            .def("setCallback", &DoubleEditSlider::setCallback)
            .def_property("range", &DoubleEditSlider::getRange, &DoubleEditSlider::setRange)
            .def_property("step", &DoubleEditSlider::getStep, &DoubleEditSlider::setStep)
            .def_property("largeStep", &DoubleEditSlider::getLargeStep, &DoubleEditSlider::setLargeStep)
            .def_property("defaultValue", &DoubleEditSlider::getDefaultValue, &DoubleEditSlider::setDefaultValue)
            .def("getModel", &DoubleEditSlider::getModel)
            .def_property("precision", &DoubleEditSlider::getPrecision, &DoubleEditSlider::setPrecision)
            .def_property("fontRole", &DoubleEditSlider::getFontRole, &DoubleEditSlider::setFontRole);

    }
}