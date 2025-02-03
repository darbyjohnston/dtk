// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiPy/FileEdit.h>

#include <dtk/ui/FileEdit.h>
#include <dtk/ui/RecentFilesModel.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dtk
{
    void fileEdit(py::module_& m)
    {
        py::class_<FileEdit, IWidget, std::shared_ptr<FileEdit> >(m, "FileEdit")
            .def(
                py::init(&FileEdit::create),
                py::arg("context"),
                py::arg("parent") = nullptr)
            .def_property("path",
                [](const std::shared_ptr<FileEdit>& w)
                {
                    return w->getPath().u8string();
                },
                [](const std::shared_ptr<FileEdit>& w, const std::string& s)
                {
                    w->setPath(s);
                })
            .def("setCallback", &FileEdit::setCallback)
            .def("setRecentFilesModel", &FileEdit::setRecentFilesModel);
    }
}