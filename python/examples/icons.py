# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

import feather_tk as ftk

import sys

# Create the context and application.
context = ftk.Context()
app = ftk.App(context, sys.argv, "icons", "Icons example")
if app.getExit() != 0:
    sys.exit(app.getExit())

# Create a window.
window = ftk.MainWindow(context, app, "icons", ftk.Size2I(1280, 960))

# Create a layout.
layout = ftk.GridLayout(context)
layout.rowBackgroundRole = ftk.ColorRole.Base
layout.spacingRole = ftk.SizeRole.SizeRole_None
scrollWidget = ftk.ScrollWidget(context, ftk.ScrollType.Both)
scrollWidget.border = False
scrollWidget.vStretch = ftk.Stretch.Expanding
scrollWidget.widget = layout
window.setWidget(scrollWidget)

# Create icons.
row = 0
for name in context.getSystemByName("feather_tk::IconSystem").names:
    icon = ftk.Icon(context, name, layout)
    layout.setGridPos(icon, row, 0)
    label = ftk.Label(context, name, layout)
    label.marginRole = ftk.SizeRole.MarginSmall
    layout.setGridPos(label, row, 1)
    row = row + 1

# Show the window and run the application.
window.show()
app.run()

# \bug Need to manually reset the window.
window = None
