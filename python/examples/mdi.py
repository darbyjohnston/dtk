# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

from tinygfx import *

import sys
        
context = tgCore.Context()
app = tgUIApp.App(context, sys.argv, "buttons", "Buttons example")
if app.getExit() != 0:
    sys.exit(app.getExit())

# Create the window.
size = tgCore.Size2I(1280, 960)
window = tgUIApp.Window(context, "buttons", size)
app.addWindow(window)

# Create the scroll widget.
scrollWidget = tgUI.ScrollWidget(context, tgUI.ScrollType.Both, window)
        
# Create the MDI canvas.
canvas = tgUI.MDICanvas(context)
scrollWidget.widget = canvas
        
# Create the MDI widgets.
random = tgCore.Random()
for i in range(0, 10):
    colorWidget = tgUI.ColorWidget(context)
    colorWidget.color = tgCore.Color4F(
        random.getF(),
        random.getF(),
        random.getF())
    canvas.addWidget(
        "Color {0}".format(i),
        tgCore.V2I(random.getI(0, size[0]), random.getI(0, size[1])),
        colorWidget)

window.show()
app.run()
# \bug Need to manually reset the window.
window = None
