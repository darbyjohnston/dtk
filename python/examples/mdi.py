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
size = ftk.Size2I(1280, 960)
window = ftk.MainWindow(context, app, "buttons", size)

# Create a scroll widget.
scrollWidget = ftk.ScrollWidget(context, ftk.ScrollType.Both)
scrollWidget.border = False
scrollWidget.vStretch = ftk.Stretch.Expanding
window.setWidget(scrollWidget)

# Create a MDI canvas.
canvas = ftk.MDICanvas(context)
scrollWidget.widget = canvas
        
# Create MDI widgets.
random = ftk.Random()
for i in range(0, 10):
    colorWidget = ftk.ColorWidget(context)
    colorWidget.color = ftk.Color4F(
        random.getF(),
        random.getF(),
        random.getF())
    canvas.addWidget(
        "Color {0}".format(i),
        ftk.V2I(random.getI(0, size[0]), random.getI(0, size[1])),
        colorWidget)

# Show the window and run the application.
window.show()
app.run()

# \bug Need to manually reset the window.
window = None
