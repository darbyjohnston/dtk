// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiPy/Menu.h>

#include <dtk/ui/Menu.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dtk
{
    void menu(py::module_& m)
    {
        py::class_<Menu, IMenuPopup, std::shared_ptr<Menu> >(m, "Menu")
            .def(
                py::init(&Menu::create),
                py::arg("context"),
                py::arg("parent") = nullptr)
            .def("getActions", &Menu::getActions)
            .def(
                "addAction",
                &Menu::addAction,
                py::arg("action"))
            .def(
                "setChecked",
                &Menu::setChecked,
                py::arg("action"),
                py::arg("checked"))
            .def(
                "setEnabled",
                &Menu::setEnabled,
                py::arg("action"),
                py::arg("enabled"))
            .def("getSubMenus", &Menu::getSubMenus)
            .def(
                "addSubMenu",
                &Menu::addSubMenu,
                py::arg("text"))
            .def(
                "setSubMenuEnabled",
                &Menu::setSubMenuEnabled,
                py::arg("menu"),
                py::arg("enabled"))
            .def("addDivider", &Menu::addDivider)
            .def("clear", &Menu::clear)
            .def(
                "shortcut",
                &Menu::shortcut,
                py::arg("key"),
                py::arg("modifiers"));
    }
}