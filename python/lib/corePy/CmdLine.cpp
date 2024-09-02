// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <corePy/CmdLine.h>

#include <dtk/core/CmdLine.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dtk
{
    void cmdLine(py::module_& m)
    {
        py::class_<ICmdLineOption, std::shared_ptr<ICmdLineOption> >(m, "ICmdLineOption");
        py::class_<ICmdLineArg, std::shared_ptr<ICmdLineArg> >(m, "ICmdLineArg");
    }
}
