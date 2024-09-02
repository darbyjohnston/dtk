# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

import dtk
from dtk import dtkUI

import sys
        
context = dtk.Context()
app = dtkUI.App(context, sys.argv, "buttons", "Buttons example")
if app.getExit() != 0:
    sys.exit(app.getExit())

# Create the window.
window = dtkUI.Window(context, "buttons", dtk.Size2I(1280, 960))
app.addWindow(window)

# Create the layout.
layout = dtkUI.VerticalLayout(context)
layout.spacingRole = dtkUI.SizeRole.SizeRoleNone
scrollWidget = dtkUI.ScrollWidget(context, dtkUI.ScrollType.Both, window)
scrollWidget.widget = layout;

# Add a bellows.
vLayout = dtkUI.VerticalLayout(context)
vLayout.marginRole = dtkUI.SizeRole.Margin
vLayout.spacingRole = dtkUI.SizeRole.SpacingSmall
for i in range(0, 10):
    dtkUI.PushButton(context, "Push Button {}".format(i), vLayout)
bellows = dtkUI.Bellows(context, "Push Buttons", layout)
bellows.widget = vLayout

# Add a bellows.
vLayout = dtkUI.VerticalLayout(context)
vLayout.marginRole = dtkUI.SizeRole.Margin
vLayout.spacingRole = dtkUI.SizeRole.SizeRoleNone
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
    button = dtkUI.ToolButton(context, "Tool Button {}".format(i), vLayout)
    if i < len(icons):
        button.icon = icons[i]
bellows = dtkUI.Bellows(context, "Tool Buttons", layout)
bellows.widget = vLayout

# Add a bellows.
vLayout = dtkUI.VerticalLayout(context)
vLayout.marginRole = dtkUI.SizeRole.Margin
vLayout.spacingRole = dtkUI.SizeRole.SizeRoleNone
for i in range(0, 10):
    dtkUI.CheckBox(context, "Check Box {}".format(i), vLayout)
bellows = dtkUI.Bellows(context, "Check Boxes", layout)
bellows.widget = vLayout

window.show()
app.run()
# \bug Need to manually reset the window.
window = None
