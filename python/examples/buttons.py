# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

from dtk import *

import sys

context = dtkCore.Context()
app = dtkUIApp.App(context, sys.argv, "buttons", "Buttons example")
if app.getExit() != 0:
    sys.exit(app.getExit())

# Create the window.
window = dtkUIApp.Window(context, "buttons", dtkCore.Size2I(1280, 960))
app.addWindow(window)

# Create the layout.
layout = dtkUI.VerticalLayout(context)
layout.marginRole = dtkUI.SizeRole.Margin
scrollWidget = dtkUI.ScrollWidget(context, dtkUI.ScrollType.Both, window)
scrollWidget.widget = layout
        
# Create push buttons
groupBox = dtkUI.GroupBox(context, "Push Buttons", layout)
hLayout = dtkUI.HorizontalLayout(context, groupBox)
pushButton = dtkUI.PushButton(context, "Click", hLayout)
pushButton.setClickedCallback(lambda: print("Click"))
pushButton = dtkUI.PushButton(context, "Text", hLayout)
pushButton.icon = "Settings"
pushButton = dtkUI.PushButton(context, "Disabled", hLayout)
pushButton.enabled = False
        
# Create tool buttons
groupBox = dtkUI.GroupBox(context, "Tool Buttons", layout)
hLayout = dtkUI.HorizontalLayout(context, groupBox)
toolButtonGroup = dtkUI.ButtonGroup(context, dtkUI.ButtonGroupType.Radio)
toolButtonGroup.setCheckedCallback(lambda index, checked: print("Tool:", index))
hLayout = dtkUI.HorizontalLayout(context, groupBox)
toolIcons = [
    "PlaybackReverse",
    "PlaybackStop",
    "PlaybackForward"
]
hLayout2 = dtkUI.HorizontalLayout(context, hLayout)
hLayout2.spacingRole = dtkUI.SizeRole.SizeRoleNone
for i in range(0, 3):
    toolButton = dtkUI.ToolButton(context, hLayout2)
    toolButton.checkable = True
    toolButton.checked = 0 == i
    toolButton.icon = toolIcons[i]
    toolButtonGroup.addButton(toolButton)
toolButton = dtkUI.ToolButton(context, "Text", hLayout)
toolButton = dtkUI.ToolButton(context, "Text", hLayout)
toolButton.icon = "Settings"
toolButton = dtkUI.ToolButton(context, "Disabled", hLayout)
toolButton.enabled = False
toolButtonGroup.addButton(toolButton)

# Create check boxes
groupBox = dtkUI.GroupBox(context, "Check Boxes", layout)
vLayout = dtkUI.VerticalLayout(context, groupBox)
checkBox = dtkUI.CheckBox(context, "Checkable", vLayout)
checkBox.setCheckedCallback(lambda checked: print("Checked:", checked))
checkBox = dtkUI.CheckBox(context, "Disabled", vLayout)
checkBox.enabled = False

window.show()
app.run()
# \bug Need to manually reset the window.
window = None
