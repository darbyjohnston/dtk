// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
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
                py::init(py::overload_cast<
                    const std::shared_ptr<Context>&,
                    const std::shared_ptr<IWidget>&>(&IntEditSlider::create)),
                py::arg("context"),
                py::arg("parent") = nullptr)
            .def(
                py::init(py::overload_cast<
                    const std::shared_ptr<Context>&,
                    const std::shared_ptr<IntModel>&,
                    const std::shared_ptr<IWidget>&>(&IntEditSlider::create)),
                py::arg("context"),
                py::arg("model"),
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