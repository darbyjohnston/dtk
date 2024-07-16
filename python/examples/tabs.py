# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

from tinygfx import *

import sys
        
context = tgCore.Context()
app = tgUIApp.App(context, sys.argv, "tabs", "Tabs example")
if app.getExit() != 0:
    sys.exit(1)

# Create the window.
window = tgUIApp.Window(context, "tabs", tgCore.Size2I(1280, 960))
app.addWindow(window)

# Create the tab widget.
tabWidget = tgUI.TabWidget(context, window)
        
# Add a tab.
layout = tgUI.VerticalLayout(context)
layout.marginRole = tgUI.SizeRole.Margin
layout.spacingRole = tgUI.SizeRole.SpacingSmall
for i in range(0, 10):
    tgUI.PushButton(context, "Push Button {}".format(i), layout)
scrollWidget = tgUI.ScrollWidget(context, tgUI.ScrollType.Both)
scrollWidget.widget = layout
tabWidget.addTab("Push Buttons", scrollWidget)

# Add a tab.
layout = tgUI.VerticalLayout(context)
layout.marginRole = tgUI.SizeRole.Margin
layout.spacingRole = tgUI.SizeRole.SizeRoleNone
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
    button = tgUI.ToolButton(context, "Tool Button {}".format(i), layout)
    if i < len(icons):
        button.icon = icons[i]
scrollWidget = tgUI.ScrollWidget(context, tgUI.ScrollType.Both)
scrollWidget.widget = layout
tabWidget.addTab("Tool Buttons", scrollWidget)

# Add a tab.
layout = tgUI.VerticalLayout(context)
layout.marginRole = tgUI.SizeRole.Margin
layout.spacingRole = tgUI.SizeRole.SizeRoleNone
for i in range(0, 10):
    tgUI.CheckBox(context, "Check Box {}".format(i), layout)
scrollWidget = tgUI.ScrollWidget(context, tgUI.ScrollType.Both)
scrollWidget.widget = layout
tabWidget.addTab("Check Boxes", scrollWidget)

window.show()
app.run()
# \bug Need to manually reset the window.
window = None
