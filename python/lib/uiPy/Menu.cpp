// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
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
            .def("getItems", &Menu::getItems)
            .def(
                "addItem",
                &Menu::addItem,
                py::arg("action"))
            .def(
                "setItemChecked",
                &Menu::setItemChecked,
                py::arg("action"),
                py::arg("checked"))
            .def(
                "setItemEnabled",
                &Menu::setItemEnabled,
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