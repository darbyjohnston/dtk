// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkUIPy/Style.h>

#include <dtkUI/Style.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace dtk
{
    namespace ui
    {
        void style(py::module_& m)
        {
            py::enum_<SizeRole>(m, "SizeRole")
                .value("SizeRoleNone", SizeRole::None)
                .value("Margin", SizeRole::Margin)
                .value("MarginSmall", SizeRole::MarginSmall)
                .value("MarginLarge", SizeRole::MarginLarge)
                .value("MarginInside", SizeRole::MarginInside)
                .value("MarginDialog", SizeRole::MarginDialog)
                .value("Spacing", SizeRole::Spacing)
                .value("SpacingSmall", SizeRole::SpacingSmall)
                .value("SpacingLarge", SizeRole::SpacingLarge)
                .value("SpacingTool", SizeRole::SpacingTool)
                .value("Border", SizeRole::Border)
                .value("ScrollArea", SizeRole::ScrollArea)
                .value("Slider", SizeRole::Slider)
                .value("Handle", SizeRole::Handle)
                .value("HandleSmall", SizeRole::HandleSmall)
                .value("Swatch", SizeRole::Swatch)
                .value("SwatchLarge", SizeRole::SwatchLarge)
                .value("Shadow", SizeRole::Shadow)
                .value("DragLength", SizeRole::DragLength)
                .export_values();

            py::enum_<ColorRole>(m, "ColorRole")
                .value("ColorRoleNone", ColorRole::None)
                .value("Window", ColorRole::Window)
                .value("Base", ColorRole::Base)
                .value("Button", ColorRole::Button)
                .value("Text", ColorRole::Text)
                .value("TextDisabled", ColorRole::TextDisabled)
                .value("Border", ColorRole::Border)
                .value("Hover", ColorRole::Hover)
                .value("Pressed", ColorRole::Pressed)
                .value("Checked", ColorRole::Checked)
                .value("KeyFocus", ColorRole::KeyFocus)
                .value("Overlay", ColorRole::Overlay)
                .value("TooltipWindow", ColorRole::TooltipWindow)
                .value("TooltipText", ColorRole::TooltipText)
                .value("Red", ColorRole::Red)
                .value("Green", ColorRole::Green)
                .value("Blue", ColorRole::Blue)
                .value("Cyan", ColorRole::Cyan)
                .value("Magenta", ColorRole::Magenta)
                .value("Yellow", ColorRole::Yellow)
                .export_values();

            py::enum_<FontRole>(m, "FontRole")
                .value("FontRoleNone", FontRole::None)
                .value("Label", FontRole::Label)
                .value("Mono", FontRole::Mono)
                .value("Title", FontRole::Title)
                .export_values();
        }
    }
}
