// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiPy/App.h>

#include <feather-tk/ui/App.h>
#include <feather-tk/ui/Settings.h>
#include <feather-tk/ui/Window.h>

#include <feather-tk/core/CmdLine.h>
#include <feather-tk/core/Context.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace pybind11::literals;
namespace py = pybind11;

namespace feather_tk
{
    void app(py::module_& m)
    {
        py::class_<App, IApp, std::shared_ptr<App> >(m, "App")
            .def(
                py::init(py::overload_cast<
                    const std::shared_ptr<Context>&,
                    const std::vector<std::string>&,
                    const std::string&,
                    const std::string&,
                    const std::vector<std::shared_ptr<ICmdLineArg> >&,
                    const std::vector<std::shared_ptr<ICmdLineOption> >&>(&App::create)),
                py::arg("context"),
                py::arg("argv"),
                py::arg("name"),
                py::arg("summary"),
                py::arg("cmdLineArgs") = std::vector<std::shared_ptr<ICmdLineArg> >(),
                py::arg("cmdLineOptions") = std::vector<std::shared_ptr<ICmdLineOption> >())
            .def("addWindow", &App::addWindow, py::arg("window"))
            .def("removeWindow", &App::removeWindow, py::arg("window"))
            .def("getWindows", &App::getWindows)
            .def("getFontSystem", &App::getFontSystem)
            .def("getIconSystem", &App::getIconSystem)
            .def("getStyle", &App::getStyle)
            .def("exit", &App::exit);
    }
}
