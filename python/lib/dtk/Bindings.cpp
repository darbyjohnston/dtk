// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <corePy/Bindings.h>
#include <uiPy/Bindings.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(dtk, m)
{
    m.doc() = "A toolkit for building DJV and other applications";
    dtk::coreBind(m);
    dtk::uiBind(m);
}
