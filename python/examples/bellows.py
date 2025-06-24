# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

import feather_tk as ftk

import sys

# Create the context and application.
context = ftk.Context()
app = ftk.App(context, sys.argv, "bellows", "Bellows example")
if app.getExit() != 0:
    sys.exit(app.getExit())

# Create a window.
window = ftk.MainWindow(context, app, "bellows", ftk.Size2I(1280, 960))

# Create a layout.
layout = ftk.VerticalLayout(context)
layout.spacingRole = ftk.SizeRole.SizeRole_None
scrollWidget = ftk.ScrollWidget(context, ftk.ScrollType.Both)
scrollWidget.border = False
scrollWidget.vStretch = ftk.Stretch.Expanding
scrollWidget.widget = layout;
window.setWidget(scrollWidget)

# Add a bellows.
vLayout = ftk.VerticalLayout(context)
vLayout.marginRole = ftk.SizeRole.MarginSmall
vLayout.spacingRole = ftk.SizeRole.SpacingSmall
for i in range(0, 10):
    ftk.PushButton(context, "Push Button {}".format(i), vLayout)
bellows = ftk.Bellows(context, "Push Buttons", layout)
bellows.widget = vLayout

# Add a bellows.
vLayout = ftk.VerticalLayout(context)
vLayout.marginRole = ftk.SizeRole.MarginSmall
vLayout.spacingRole = ftk.SizeRole.SpacingSmall
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
    button = ftk.ToolButton(context, "Tool Button {}".format(i), vLayout)
    if i < len(icons):
        button.icon = icons[i]
bellows = ftk.Bellows(context, "Tool Buttons", layout)
bellows.widget = vLayout

# Add a bellows.
vLayout = ftk.VerticalLayout(context)
vLayout.marginRole = ftk.SizeRole.MarginSmall
vLayout.spacingRole = ftk.SizeRole.SpacingSmall
for i in range(0, 10):
    ftk.CheckBox(context, "Check Box {}".format(i), vLayout)
bellows = ftk.Bellows(context, "Check Boxes", layout)
bellows.widget = vLayout

# Show the window and run the application.
window.show()
app.run()

# \bug Need to manually reset the window.
window = None
