// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiPy/FileBrowser.h>

#include <feather-tk/ui/FileBrowser.h>
#include <feather-tk/ui/IWindow.h>
#include <feather-tk/ui/RecentFilesModel.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace feather_tk
{
    void fileBrowser(py::module_& m)
    {
        py::enum_<FileBrowserMode>(m, "FileBrowserMode")
            .value("File", FileBrowserMode::File)
            .value("Dir", FileBrowserMode::Dir)
            .export_values();

        py::class_<FileBrowserModel, std::shared_ptr<FileBrowserModel> >(m, "FileBrowserModel")
            .def(
                py::init(&FileBrowserModel::create),
                py::arg("context"))
            .def_property(
                "path",
                &FileBrowserModel::getPath,
                &FileBrowserModel::setPath)
            .def("observePath", &FileBrowserModel::observePath)
            .def("forward", &FileBrowserModel::forward)
            .def("observeHasForward", &FileBrowserModel::observeHasForward)
            .def("back", &FileBrowserModel::back)
            .def("observeHasBack", &FileBrowserModel::observeHasBack)
            .def_property(
                "options",
                &FileBrowserModel::getOptions,
                &FileBrowserModel::setOptions)
            .def("observeOptions", &FileBrowserModel::observeOptions)
            .def_property(
                "extensions",
                &FileBrowserModel::getExtensions,
                &FileBrowserModel::setExtensions)
            .def("observeExtensions", &FileBrowserModel::observeExtensions)
            .def_property(
                "extension",
                &FileBrowserModel::getExtension,
                &FileBrowserModel::setExtension)
            .def("observeExtension", &FileBrowserModel::observeExtension);

        py::class_<FileBrowserSystem, ISystem, std::shared_ptr<FileBrowserSystem> >(m, "FileBrowserSystem")
            .def(
                py::init(&FileBrowserSystem::create),
                py::arg("context"))
            .def("open", &FileBrowserSystem::open,
                py::arg("window"),
                py::arg("callback"),
                py::arg("fileName"),
                py::arg("mode"))
            .def_property(
                "nativeFileDialog",
                &FileBrowserSystem::isNativeFileDialog,
                &FileBrowserSystem::setNativeFileDialog)
            .def_property_readonly(
                "model",
                &FileBrowserSystem::getModel)
            .def_property(
                "recentFilesModel",
                &FileBrowserSystem::getRecentFilesModel,
                &FileBrowserSystem::setRecentFilesModel);
    }
}