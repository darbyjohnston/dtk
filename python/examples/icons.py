# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

import dtk

import sys

# Create the context and application.
context = dtk.Context()
app = dtk.App(context, sys.argv, "icons", "Icons example")
if app.getExit() != 0:
    sys.exit(app.getExit())

# Create a window.
window = dtk.MainWindow(context, app, "icons", dtk.Size2I(1280, 960))

# Create a layout.
layout = dtk.GridLayout(context)
layout.rowBackgroundRole = dtk.ColorRole.Base
layout.spacingRole = dtk.SizeRole.SizeRole_None
scrollWidget = dtk.ScrollWidget(context, dtk.ScrollType.Both)
scrollWidget.border = False
scrollWidget.vStretch = dtk.Stretch.Expanding
scrollWidget.widget = layout
window.setWidget(scrollWidget)

# Create icons.
row = 0
for name in context.getSystemByName("dtk::IconSystem").names:
    icon = dtk.Icon(context, name, layout)
    layout.setGridPos(icon, row, 0)
    label = dtk.Label(context, name, layout)
    label.marginRole = dtk.SizeRole.MarginSmall
    layout.setGridPos(label, row, 1)
    row = row + 1

# Show the window and run the application.
window.show()
app.run()

# \bug Need to manually reset the window.
window = None
