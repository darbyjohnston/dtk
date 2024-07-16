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
window = tgUIApp.Window(context, "buttons", tgCore.Size2I(1280, 960))
app.addWindow(window)

# Create the layout.
layout = tgUI.VerticalLayout(context)
layout.spacingRole = tgUI.SizeRole.SizeRoleNone
scrollWidget = tgUI.ScrollWidget(context, tgUI.ScrollType.Both, window)
scrollWidget.widget = layout;

# Add a bellows.
vLayout = tgUI.VerticalLayout(context)
vLayout.marginRole = tgUI.SizeRole.Margin
vLayout.spacingRole = tgUI.SizeRole.SpacingSmall
for i in range(0, 10):
    tgUI.PushButton(context, "Push Button {}".format(i), vLayout)
bellows = tgUI.Bellows(context, "Push Buttons", layout)
bellows.widget = vLayout

# Add a bellows.
vLayout = tgUI.VerticalLayout(context)
vLayout.marginRole = tgUI.SizeRole.Margin
vLayout.spacingRole = tgUI.SizeRole.SizeRoleNone
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
    button = tgUI.ToolButton(context, "Tool Button {}".format(i), vLayout)
    if i < len(icons):
        button.icon = icons[i]
bellows = tgUI.Bellows(context, "Tool Buttons", layout)
bellows.widget = vLayout

# Add a bellows.
vLayout = tgUI.VerticalLayout(context)
vLayout.marginRole = tgUI.SizeRole.Margin
vLayout.spacingRole = tgUI.SizeRole.SizeRoleNone
for i in range(0, 10):
    tgUI.CheckBox(context, "Check Box {}".format(i), vLayout)
bellows = tgUI.Bellows(context, "Check Boxes", layout)
bellows.widget = vLayout

window.show()
app.run()
# \bug Need to manually reset the window.
window = None
