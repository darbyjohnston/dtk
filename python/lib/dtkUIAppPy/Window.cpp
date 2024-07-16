// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkUIAppPy/Window.h>

#include <dtkUIApp/Window.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dtk
{
    namespace ui_app
    {
        class PyWindow : public ui::Window
        {
        public:
            static std::shared_ptr<PyWindow> create(
                const std::shared_ptr<core::Context>& context,
                const std::string& name,
                const core::Size2I& size)
            {
                auto out = std::shared_ptr<PyWindow>(new PyWindow);
                out->_init(context, name, size);
                return out;
            }

            virtual void drawEvent(const core::Box2I& drawRect, const ui::DrawEvent& event) override
            {
                PYBIND11_OVERRIDE(
                    void,
                    ui::Window,
                    drawEvent,
                    drawRect,
                    event);
            }
        };

        void window(py::module_& m)
        {
            py::class_<ui::Window, ui::IWindow, std::shared_ptr<ui::Window>, PyWindow>(m, "Window")
                .def(
                    py::init(&ui::Window::create, &PyWindow::create),
                    py::arg("context"),
                    py::arg("name"),
                    py::arg("size"))
                .def("show", &ui::Window::show);
        }
    }
}
