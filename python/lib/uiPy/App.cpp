// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiPy/App.h>

#include <dtk/ui/App.h>
#include <dtk/ui/Window.h>

#include <dtk/core/CmdLine.h>
#include <dtk/core/Context.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace pybind11::literals;
namespace py = pybind11;

namespace dtk
{
    void app(py::module_& m)
    {
        py::class_<App, IApp, std::shared_ptr<App> >(m, "App")
            .def(
                py::init(&App::create),
                py::arg("context"),
                py::arg("argv"),
                py::arg("name"),
                py::arg("summary"),
                py::arg("cmdLineArgs") = std::vector<std::shared_ptr<ICmdLineArg> >(),
                py::arg("cmdLineOptions") = std::vector<std::shared_ptr<ICmdLineOption> >())
            .def("addWindow", &App::addWindow, py::arg("window"))
            .def("removeWindow", &App::removeWindow, py::arg("window"))
            .def("exit", &App::exit);
    }
}
