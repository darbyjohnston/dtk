// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <corePy/String.h>

#include <feather-tk/core/String.h>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include <sstream>

namespace py = pybind11;

namespace feather_tk
{
    void string(py::module_& m)
    {
        m.def(
            "getLoremIpsum",
            py::overload_cast<>(&getLoremIpsum));
        m.def(
            "getLoremIpsum",
            py::overload_cast<size_t>(&getLoremIpsum),
            py::arg("lineCount"));
    }
}
