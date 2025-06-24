// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <corePy/Bindings.h>
#include <uiPy/Bindings.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(feather_tk, m)
{
    m.doc() = "A lightweight toolkit for building cross-platform applications.";
    feather_tk::coreBind(m);
    feather_tk::uiBind(m);
}
