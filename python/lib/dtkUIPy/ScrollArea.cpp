// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkUIPy/ScrollArea.h>

#include <dtkUI/ScrollArea.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dtk
{
    namespace ui
    {
        void scrollArea(py::module_& m)
        {
            py::enum_<ScrollType>(m, "ScrollType")
                .value("Horizontal", ScrollType::Horizontal)
                .value("Vertical", ScrollType::Vertical)
                .value("Both", ScrollType::Both)
                .value("Menu", ScrollType::Menu)
                .export_values();
        }
    }
}
