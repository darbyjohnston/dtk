# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

import dtk

import sys

# Create the context and application.
context = dtk.Context()
app = dtk.App(context, sys.argv, "buttons", "Buttons example")
if app.getExit() != 0:
    sys.exit(app.getExit())

# Create a window.
window = dtk.MainWindow(context, app, "buttons", dtk.Size2I(1280, 960))

# Create a layout.
layout = dtk.VerticalLayout(context)
layout.marginRole = dtk.SizeRole.Margin
scrollWidget = dtk.ScrollWidget(context, dtk.ScrollType.Both)
scrollWidget.border = False
scrollWidget.vStretch = dtk.Stretch.Expanding
scrollWidget.widget = layout
window.setWidget(scrollWidget)

# Create integer sliders.
groupBox = dtk.GroupBox(context, "Integer sliders", layout)
vLayout = dtk.VerticalLayout(context, groupBox)
intEditSlider = dtk.IntEditSlider(context, vLayout)
intEditSlider.setCallback(lambda value: print("Int:", value))
intEditSlider = dtk.IntEditSlider(context, vLayout)
intEditSlider.range = dtk.RangeI(100, 200)
intEditSlider.setCallback(lambda value: print("Int:", value))
intEditSlider = dtk.IntEditSlider(context, vLayout)
intEditSlider.range = dtk.RangeI(-100, 100)
intEditSlider.setCallback(lambda value: print("Int:", value))
        
# Create float sliders.
groupBox = dtk.GroupBox(context, "Float sliders", layout)
vLayout = dtk.VerticalLayout(context, groupBox)
floatEditSlider = dtk.FloatEditSlider(context, vLayout)
floatEditSlider.setCallback(lambda value: print("Float:", value))
floatEditSlider = dtk.FloatEditSlider(context, vLayout)
floatEditSlider.range = dtk.RangeF(100, 200)
floatEditSlider.setCallback(lambda value: print("Float:", value))
floatEditSlider = dtk.FloatEditSlider(context, vLayout)
floatEditSlider.range = dtk.RangeF(-100, 100)
floatEditSlider.setCallback(lambda value: print("Float:", value))
        
# Create double sliders.
groupBox = dtk.GroupBox(context, "Double sliders", layout)
vLayout = dtk.VerticalLayout(context, groupBox)
doubleEditSlider = dtk.DoubleEditSlider(context, vLayout)
doubleEditSlider.setCallback(lambda value: print("Double:", value))
doubleEditSlider = dtk.DoubleEditSlider(context, vLayout)
doubleEditSlider.range = dtk.RangeD(100, 200)
doubleEditSlider.setCallback(lambda value: print("Double:", value))
doubleEditSlider = dtk.DoubleEditSlider(context, vLayout)
doubleEditSlider.range = dtk.RangeD(-100, 100)
doubleEditSlider.setCallback(lambda value: print("Double:", value))

# Show the window and run the application.
window.show()
app.run()

# \bug Need to manually reset the window.
window = None
