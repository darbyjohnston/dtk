# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

import feather_tk as ftk

import sys

# Create the context and application.
context = ftk.Context()
app = ftk.App(context, sys.argv, "buttons", "Buttons example")
if app.getExit() != 0:
    sys.exit(app.getExit())

# Create a window.
window = ftk.MainWindow(context, app, "buttons", ftk.Size2I(1280, 960))

# Create a layout.
layout = ftk.VerticalLayout(context)
layout.marginRole = ftk.SizeRole.Margin
scrollWidget = ftk.ScrollWidget(context, ftk.ScrollType.Both)
scrollWidget.border = False
scrollWidget.vStretch = ftk.Stretch.Expanding
scrollWidget.widget = layout
window.setWidget(scrollWidget)

# Create integer sliders.
groupBox = ftk.GroupBox(context, "Integer sliders", layout)
vLayout = ftk.VerticalLayout(context, groupBox)
intEditSlider = ftk.IntEditSlider(context, vLayout)
intEditSlider.setCallback(lambda value: print("Int:", value))
intEditSlider = ftk.IntEditSlider(context, vLayout)
intEditSlider.range = ftk.RangeI(100, 200)
intEditSlider.setCallback(lambda value: print("Int:", value))
intEditSlider = ftk.IntEditSlider(context, vLayout)
intEditSlider.range = ftk.RangeI(-100, 100)
intEditSlider.setCallback(lambda value: print("Int:", value))
        
# Create float sliders.
groupBox = ftk.GroupBox(context, "Float sliders", layout)
vLayout = ftk.VerticalLayout(context, groupBox)
floatEditSlider = ftk.FloatEditSlider(context, vLayout)
floatEditSlider.setCallback(lambda value: print("Float:", value))
floatEditSlider = ftk.FloatEditSlider(context, vLayout)
floatEditSlider.range = ftk.RangeF(100, 200)
floatEditSlider.setCallback(lambda value: print("Float:", value))
floatEditSlider = ftk.FloatEditSlider(context, vLayout)
floatEditSlider.range = ftk.RangeF(-100, 100)
floatEditSlider.setCallback(lambda value: print("Float:", value))
        
# Create double sliders.
groupBox = ftk.GroupBox(context, "Double sliders", layout)
vLayout = ftk.VerticalLayout(context, groupBox)
doubleEditSlider = ftk.DoubleEditSlider(context, vLayout)
doubleEditSlider.setCallback(lambda value: print("Double:", value))
doubleEditSlider = ftk.DoubleEditSlider(context, vLayout)
doubleEditSlider.range = ftk.RangeD(100, 200)
doubleEditSlider.setCallback(lambda value: print("Double:", value))
doubleEditSlider = ftk.DoubleEditSlider(context, vLayout)
doubleEditSlider.range = ftk.RangeD(-100, 100)
doubleEditSlider.setCallback(lambda value: print("Double:", value))

# Show the window and run the application.
window.show()
app.run()

# \bug Need to manually reset the window.
window = None
