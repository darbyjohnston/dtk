// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiPy/TabWidget.h>

#include <dtk/ui/TabWidget.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dtk
{
    namespace ui
    {
        void tabWidget(py::module_& m)
        {
            py::class_<TabWidget, IWidget, std::shared_ptr<TabWidget> >(m, "TabWidget")
                .def(
                    py::init(&TabWidget::create),
                    py::arg("context"),
                    py::arg("parent") = nullptr)
                .def_property_readonly("tabs", &TabWidget::getTabs)
                .def("addTab", &TabWidget::addTab)
                .def("clearTabs", &TabWidget::clearTabs)
                .def_property("currentTab", &TabWidget::getCurrentTab, &TabWidget::setCurrentTab)
                .def("setCallback", &TabWidget::setCallback);
        }
    }
}
