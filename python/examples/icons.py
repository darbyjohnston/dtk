# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

import dtk

import sys

context = dtk.Context()
app = dtk.App(context, sys.argv, "icons", "Icons example")
if app.getExit() != 0:
    sys.exit(app.getExit())

# Create the window.
window = dtk.Window(context, "icons", dtk.Size2I(1280, 960))
app.addWindow(window)

# Create the layout.
layout = dtk.GridLayout(context)
layout.marginRole = dtk.SizeRole.MarginSmall
layout.spacingRole = dtk.SizeRole.SpacingSmall
scrollWidget = dtk.ScrollWidget(context, dtk.ScrollType.Both, window)
scrollWidget.widget = layout
        
# Create the icons.
index = 0
for name in context.getSystemByName("dtk::IconSystem").names:
    icon = dtk.Icon(context, name, layout)
    layout.setGridPos(icon, index, 0)
    label = dtk.Label(context, name, layout)
    layout.setGridPos(label, index, 1)
    index = index + 1

window.show()
app.run()
# \bug Need to manually reset the window.
window = None
