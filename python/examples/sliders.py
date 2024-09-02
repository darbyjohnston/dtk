# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

import dtk
from dtk import dtkUI

import sys
        
context = dtk.Context()
app = dtkUI.App(context, sys.argv, "buttons", "Buttons example")
if app.getExit() != 0:
    sys.exit(app.getExit())

# Create the window.
window = dtkUI.Window(context, "buttons", dtk.Size2I(1280, 960))
app.addWindow(window)

# Create the layout.
layout = dtkUI.VerticalLayout(context)
layout.marginRole = dtkUI.SizeRole.Margin
scrollWidget = dtkUI.ScrollWidget(context, dtkUI.ScrollType.Both, window)
scrollWidget.widget = layout
        
# Create integer sliders.
groupBox = dtkUI.GroupBox(context, "Integer sliders", layout)
vLayout = dtkUI.VerticalLayout(context, groupBox)
intEditSlider = dtkUI.IntEditSlider(context, None, vLayout)
intEditSlider.setCallback(lambda value: print("Int:", value))
intEditSlider = dtkUI.IntEditSlider(context, None, vLayout)
intEditSlider.range = dtk.RangeI(100, 200)
intEditSlider.setCallback(lambda value: print("Int:", value))
intEditSlider = dtkUI.IntEditSlider(context, None, vLayout)
intEditSlider.range = dtk.RangeI(-100, 100)
intEditSlider.setCallback(lambda value: print("Int:", value))
        
# Create float sliders.
groupBox = dtkUI.GroupBox(context, "Float sliders", layout)
vLayout = dtkUI.VerticalLayout(context, groupBox)
floatEditSlider = dtkUI.FloatEditSlider(context, None, vLayout)
floatEditSlider.setCallback(lambda value: print("Float:", value))
floatEditSlider = dtkUI.FloatEditSlider(context, None, vLayout)
floatEditSlider.range = dtk.RangeF(100, 200)
floatEditSlider.setCallback(lambda value: print("Float:", value))
floatEditSlider = dtkUI.FloatEditSlider(context, None, vLayout)
floatEditSlider.range = dtk.RangeF(-100, 100)
floatEditSlider.setCallback(lambda value: print("Float:", value))
        
# Create double sliders.
groupBox = dtkUI.GroupBox(context, "Double sliders", layout)
vLayout = dtkUI.VerticalLayout(context, groupBox)
doubleEditSlider = dtkUI.DoubleEditSlider(context, None, vLayout)
doubleEditSlider.setCallback(lambda value: print("Double:", value))
doubleEditSlider = dtkUI.DoubleEditSlider(context, None, vLayout)
doubleEditSlider.range = dtk.RangeD(100, 200)
doubleEditSlider.setCallback(lambda value: print("Double:", value))
doubleEditSlider = dtkUI.DoubleEditSlider(context, None, vLayout)
doubleEditSlider.range = dtk.RangeD(-100, 100)
doubleEditSlider.setCallback(lambda value: print("Double:", value))

window.show()
app.run()
# \bug Need to manually reset the window.
window = None
