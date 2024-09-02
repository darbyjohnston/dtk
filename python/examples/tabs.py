# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

import dtk

import sys
        
context = dtk.Context()
app = dtk.App(context, sys.argv, "tabs", "Tabs example")
if app.getExit() != 0:
    sys.exit(1)

# Create the window.
window = dtk.Window(context, "tabs", dtk.Size2I(1280, 960))
app.addWindow(window)

# Create the tab widget.
tabWidget = dtk.TabWidget(context, window)
        
# Add a tab.
layout = dtk.VerticalLayout(context)
layout.marginRole = dtk.SizeRole.Margin
layout.spacingRole = dtk.SizeRole.SpacingSmall
for i in range(0, 10):
    dtk.PushButton(context, "Push Button {}".format(i), layout)
scrollWidget = dtk.ScrollWidget(context, dtk.ScrollType.Both)
scrollWidget.widget = layout
tabWidget.addTab("Push Buttons", scrollWidget)

# Add a tab.
layout = dtk.VerticalLayout(context)
layout.marginRole = dtk.SizeRole.Margin
layout.spacingRole = dtk.SizeRole.SizeRoleNone
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
    button = dtk.ToolButton(context, "Tool Button {}".format(i), layout)
    if i < len(icons):
        button.icon = icons[i]
scrollWidget = dtk.ScrollWidget(context, dtk.ScrollType.Both)
scrollWidget.widget = layout
tabWidget.addTab("Tool Buttons", scrollWidget)

# Add a tab.
layout = dtk.VerticalLayout(context)
layout.marginRole = dtk.SizeRole.Margin
layout.spacingRole = dtk.SizeRole.SizeRoleNone
for i in range(0, 10):
    dtk.CheckBox(context, "Check Box {}".format(i), layout)
scrollWidget = dtk.ScrollWidget(context, dtk.ScrollType.Both)
scrollWidget.widget = layout
tabWidget.addTab("Check Boxes", scrollWidget)

window.show()
app.run()
# \bug Need to manually reset the window.
window = None
