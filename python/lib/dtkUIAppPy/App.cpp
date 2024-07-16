// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkUIAppPy/App.h>

#include <dtkUIApp/App.h>
#include <dtkUIApp/Window.h>

#include <dtkBaseApp/CmdLine.h>

#include <dtkCore/Context.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace pybind11::literals;
namespace py = pybind11;

namespace dtk
{
    namespace ui_app
    {
        void app(py::module_& m)
        {
            py::class_<ui::App, app::IApp, std::shared_ptr<ui::App> >(m, "App")
                .def(
                    py::init(&ui::App::create),
                    py::arg("context"),
                    py::arg("argv"),
                    py::arg("name"),
                    py::arg("summary"),
                    py::arg("cmdLineArgs") = std::vector<std::shared_ptr<app::ICmdLineArg> >(),
                    py::arg("cmdLineOptions") = std::vector<std::shared_ptr<app::ICmdLineOption> >())
                .def("addWindow", &ui::App::addWindow, py::arg("window"))
                .def("removeWindow", &ui::App::removeWindow, py::arg("window"))
                .def("exit", &ui::App::exit);
        }
    }
}
