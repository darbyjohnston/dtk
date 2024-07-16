// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkCorePy/ObservableList.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dtk
{
    namespace core
    {
        void observableList(py::module_& m)
        {
            observableList<int>(m, "I");
            observableList<float>(m, "F");
            observableList<double>(m, "D");
            observableList<bool>(m, "Bool");
        }
    }
}
