# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

import dtk
from dtk import dtkUI

import sys
        
context = dtk.Context()
app = dtkUI.App(context, sys.argv, "tabs", "Tabs example")
if app.getExit() != 0:
    sys.exit(1)

# Create the window.
window = dtkUI.Window(context, "tabs", dtk.Size2I(1280, 960))
app.addWindow(window)

# Create the tab widget.
tabWidget = dtkUI.TabWidget(context, window)
        
# Add a tab.
layout = dtkUI.VerticalLayout(context)
layout.marginRole = dtkUI.SizeRole.Margin
layout.spacingRole = dtkUI.SizeRole.SpacingSmall
for i in range(0, 10):
    dtkUI.PushButton(context, "Push Button {}".format(i), layout)
scrollWidget = dtkUI.ScrollWidget(context, dtkUI.ScrollType.Both)
scrollWidget.widget = layout
tabWidget.addTab("Push Buttons", scrollWidget)

# Add a tab.
layout = dtkUI.VerticalLayout(context)
layout.marginRole = dtkUI.SizeRole.Margin
layout.spacingRole = dtkUI.SizeRole.SizeRoleNone
icons = [
    "Audio",
    "Close",
    "Copy",
    "Directory",
    "File",
    "FrameNext",
    "FramePrev",
    "Mute",
    "Search",
    "Volume"
]
for i in range(0, 10):
    button = dtkUI.ToolButton(context, "Tool Button {}".format(i), layout)
    if i < len(icons):
        button.icon = icons[i]
scrollWidget = dtkUI.ScrollWidget(context, dtkUI.ScrollType.Both)
scrollWidget.widget = layout
tabWidget.addTab("Tool Buttons", scrollWidget)

# Add a tab.
layout = dtkUI.VerticalLayout(context)
layout.marginRole = dtkUI.SizeRole.Margin
layout.spacingRole = dtkUI.SizeRole.SizeRoleNone
for i in range(0, 10):
    dtkUI.CheckBox(context, "Check Box {}".format(i), layout)
scrollWidget = dtkUI.ScrollWidget(context, dtkUI.ScrollType.Both)
scrollWidget.widget = layout
tabWidget.addTab("Check Boxes", scrollWidget)

window.show()
app.run()
# \bug Need to manually reset the window.
window = None
