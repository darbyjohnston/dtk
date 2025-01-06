// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <pybind11/pybind11.h>

namespace dtk
{
    template<typename T>
    void observableValue(pybind11::module_&, const std::string& type);
    void observableValue(pybind11::module_&);
}

#include <corePy/ObservableValueInline.h>
