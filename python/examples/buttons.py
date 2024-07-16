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
layout.marginRole = tgUI.SizeRole.Margin
scrollWidget = tgUI.ScrollWidget(context, tgUI.ScrollType.Both, window)
scrollWidget.widget = layout
        
# Create push buttons
groupBox = tgUI.GroupBox(context, "Push Buttons", layout)
hLayout = tgUI.HorizontalLayout(context, groupBox)
pushButton = tgUI.PushButton(context, "Click", hLayout)
pushButton.setClickedCallback(lambda: print("Click"))
pushButton = tgUI.PushButton(context, "Text", hLayout)
pushButton.icon = "Settings"
pushButton = tgUI.PushButton(context, "Disabled", hLayout)
pushButton.enabled = False
        
# Create tool buttons
groupBox = tgUI.GroupBox(context, "Tool Buttons", layout)
hLayout = tgUI.HorizontalLayout(context, groupBox)
toolButtonGroup = tgUI.ButtonGroup(context, tgUI.ButtonGroupType.Radio)
toolButtonGroup.setCheckedCallback(lambda index, checked: print("Tool:", index))
hLayout = tgUI.HorizontalLayout(context, groupBox)
toolIcons = [
    "PlaybackReverse",
    "PlaybackStop",
    "PlaybackForward"
]
hLayout2 = tgUI.HorizontalLayout(context, hLayout)
hLayout2.spacingRole = tgUI.SizeRole.SizeRoleNone
for i in range(0, 3):
    toolButton = tgUI.ToolButton(context, hLayout2)
    toolButton.checkable = True
    toolButton.checked = 0 == i
    toolButton.icon = toolIcons[i]
    toolButtonGroup.addButton(toolButton)
toolButton = tgUI.ToolButton(context, "Text", hLayout)
toolButton = tgUI.ToolButton(context, "Text", hLayout)
toolButton.icon = "Settings"
toolButton = tgUI.ToolButton(context, "Disabled", hLayout)
toolButton.enabled = False
toolButtonGroup.addButton(toolButton)

# Create check boxes
groupBox = tgUI.GroupBox(context, "Check Boxes", layout)
vLayout = tgUI.VerticalLayout(context, groupBox)
checkBox = tgUI.CheckBox(context, "Checkable", vLayout)
checkBox.setCheckedCallback(lambda checked: print("Checked:", checked))
checkBox = tgUI.CheckBox(context, "Disabled", vLayout)
checkBox.enabled = False

window.show()
app.run()
# \bug Need to manually reset the window.
window = None
