// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkUIPy/MDICanvas.h>

#include <dtkUI/MDICanvas.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dtk
{
    namespace ui
    {
        void mdiCanvas(py::module_& m)
        {
            py::class_<MDICanvas, IWidget, std::shared_ptr<MDICanvas> >(m, "MDICanvas")
                .def(
                    py::init(&MDICanvas::create),
                    py::arg("context"),
                    py::arg("parent") = nullptr)
                .def_property("canvasSize", &MDICanvas::getCanvasSize, &MDICanvas::setCanvasSize)
                .def_property("gridSize", &MDICanvas::getGridSize, &MDICanvas::setGridSize)
                .def("addWidget", &MDICanvas::addWidget);
        }
    }
}
