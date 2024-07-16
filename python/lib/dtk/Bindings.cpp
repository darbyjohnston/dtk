// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkCorePy/Bindings.h>
#include <dtkBaseAppPy/Bindings.h>
#include <dtkUIPy/Bindings.h>
#include <dtkUIAppPy/Bindings.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(dtk, m)
{
    m.doc() = "A toolkit for building DJV and other applications";
    dtk::core::bind(m);
    dtk::app::bind(m);
    dtk::ui::bind(m);
    dtk::ui_app::bind(m);
}
