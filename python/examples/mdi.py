# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

import dtk

import sys
        
context = dtk.Context()
app = dtk.App(context, sys.argv, "buttons", "Buttons example")
if app.getExit() != 0:
    sys.exit(app.getExit())

# Create the window.
size = dtk.Size2I(1280, 960)
window = dtk.MainWindow(context, app, "buttons", size)
app.addWindow(window)

# Create the scroll widget.
scrollWidget = dtk.ScrollWidget(context, dtk.ScrollType.Both)
scrollWidget.border = False
scrollWidget.vStretch = dtk.Stretch.Expanding
window.setWidget(scrollWidget)

# Create the MDI canvas.
canvas = dtk.MDICanvas(context)
scrollWidget.widget = canvas
        
# Create the MDI widgets.
random = dtk.Random()
for i in range(0, 10):
    colorWidget = dtk.ColorWidget(context)
    colorWidget.color = dtk.Color4F(
        random.getF(),
        random.getF(),
        random.getF())
    canvas.addWidget(
        "Color {0}".format(i),
        dtk.V2I(random.getI(0, size[0]), random.getI(0, size[1])),
        colorWidget)

window.show()
app.run()
# \bug Need to manually reset the window.
window = None
