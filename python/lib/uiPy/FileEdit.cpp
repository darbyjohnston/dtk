// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiPy/FileEdit.h>

#include <dtk/ui/FileEdit.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dtk
{
    namespace ui
    {
        void fileEdit(py::module_& m)
        {
            py::class_<FileEdit, IWidget, std::shared_ptr<FileEdit> >(m, "FileEdit")
                .def(
                    py::init(&FileEdit::create),
                    py::arg("context"),
                    py::arg("parent") = nullptr)
                .def_property("path", &FileEdit::getPath, &FileEdit::setPath)
                .def("setCallback", &FileEdit::setCallback);
        }
    }
}
