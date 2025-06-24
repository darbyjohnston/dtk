// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiPy/TabBar.h>

#include <feather-tk/ui/TabBar.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace feather_tk
{
    void tabBar(py::module_& m)
    {
        py::class_<TabBar, IWidget, std::shared_ptr<TabBar> >(m, "TabBar")
            .def(
                py::init(&TabBar::create),
                py::arg("context"),
                py::arg("parent") = nullptr)
            .def_property("tabs", &TabBar::getTabs, &TabBar::setTabs)
            .def("addTab", &TabBar::addTab)
            .def("clearTabs", &TabBar::clearTabs)
            .def_property("currentTab", &TabBar::getCurrentTab, &TabBar::setCurrentTab)
            .def("setCallback", &TabBar::setCallback);
    }
}