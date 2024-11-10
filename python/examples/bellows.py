# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

import dtk

import sys
        
context = dtk.Context()
app = dtk.App(context, sys.argv, "buttons", "Buttons example")
if app.getExit() != 0:
    sys.exit(app.getExit())

# Create the window.
window = dtk.Window(context, "buttons", dtk.Size2I(1280, 960))
app.addWindow(window)

# Create the layout.
layout = dtk.VerticalLayout(context)
layout.spacingRole = dtk.SizeRole.SizeRole_None
scrollWidget = dtk.ScrollWidget(context, dtk.ScrollType.Both, window)
scrollWidget.widget = layout;

# Add a bellows.
vLayout = dtk.VerticalLayout(context)
vLayout.marginRole = dtk.SizeRole.Margin
vLayout.spacingRole = dtk.SizeRole.SpacingSmall
for i in range(0, 10):
    dtk.PushButton(context, "Push Button {}".format(i), vLayout)
bellows = dtk.Bellows(context, "Push Buttons", layout)
bellows.widget = vLayout

# Add a bellows.
vLayout = dtk.VerticalLayout(context)
vLayout.marginRole = dtk.SizeRole.Margin
vLayout.spacingRole = dtk.SizeRole.SizeRole_None
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
    button = dtk.ToolButton(context, "Tool Button {}".format(i), vLayout)
    if i < len(icons):
        button.icon = icons[i]
bellows = dtk.Bellows(context, "Tool Buttons", layout)
bellows.widget = vLayout

# Add a bellows.
vLayout = dtk.VerticalLayout(context)
vLayout.marginRole = dtk.SizeRole.Margin
vLayout.spacingRole = dtk.SizeRole.SizeRole_None
for i in range(0, 10):
    dtk.CheckBox(context, "Check Box {}".format(i), vLayout)
bellows = dtk.Bellows(context, "Check Boxes", layout)
bellows.widget = vLayout

window.show()
app.run()
# \bug Need to manually reset the window.
window = None
