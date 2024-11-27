// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiPy/FloatEditSlider.h>

#include <dtk/ui/FloatEditSlider.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dtk
{
    void floatEditSlider(py::module_& m)
    {
        py::class_<FloatEditSlider, IWidget, std::shared_ptr<FloatEditSlider> >(m, "FloatEditSlider")
            .def(
                py::init(py::overload_cast<
                    const std::shared_ptr<Context>&,
                    const std::shared_ptr<IWidget>&>(&FloatEditSlider::create)),
                py::arg("context"),
                py::arg("parent") = nullptr)
            .def(
                py::init(py::overload_cast<
                    const std::shared_ptr<Context>&,
                    const std::shared_ptr<FloatModel>&,
                    const std::shared_ptr<IWidget>&>(&FloatEditSlider::create)),
                py::arg("context"),
                py::arg("model"),
                py::arg("parent") = nullptr)
            .def_property("value", &FloatEditSlider::getValue, &FloatEditSlider::setValue)
            .def("setCallback", &FloatEditSlider::setCallback)
            .def_property("range", &FloatEditSlider::getRange, &FloatEditSlider::setRange)
            .def_property("step", &FloatEditSlider::getStep, &FloatEditSlider::setStep)
            .def_property("largeStep", &FloatEditSlider::getLargeStep, &FloatEditSlider::setLargeStep)
            .def_property("defaultValue", &FloatEditSlider::getDefaultValue, &FloatEditSlider::setDefaultValue)
            .def("getModel", &FloatEditSlider::getModel)
            .def_property("precision", &FloatEditSlider::getPrecision, &FloatEditSlider::setPrecision)
            .def_property("fontRole", &FloatEditSlider::getFontRole, &FloatEditSlider::setFontRole);
    }
}