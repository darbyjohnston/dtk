// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiPy/FileBrowser.h>

#include <dtk/ui/FileBrowser.h>
#include <dtk/ui/IWindow.h>
#include <dtk/ui/RecentFilesModel.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dtk
{
    void fileBrowser(py::module_& m)
    {
        py::class_<FileBrowserSystem, ISystem, std::shared_ptr<FileBrowserSystem> >(m, "FileBrowserSystem")
            .def(
                py::init(&FileBrowserSystem::create),
                py::arg("context"))
            .def("open", &FileBrowserSystem::open,
                py::arg("window"),
                py::arg("callback"))
            .def_property(
                "nativeFileDialog",
                &FileBrowserSystem::isNativeFileDialog,
                &FileBrowserSystem::setNativeFileDialog)
            .def_property(
                "path",
                &FileBrowserSystem::getPath,
                &FileBrowserSystem::setPath)
            .def_property(
                "options",
                &FileBrowserSystem::getOptions,
                &FileBrowserSystem::setOptions)
            .def_property_readonly(
                "recentFilesModel",
                &FileBrowserSystem::getRecentFilesModel);
    }
}