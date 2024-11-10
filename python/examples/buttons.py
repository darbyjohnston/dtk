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
layout.marginRole = dtk.SizeRole.Margin
scrollWidget = dtk.ScrollWidget(context, dtk.ScrollType.Both, window)
scrollWidget.widget = layout
        
# Create push buttons.
groupBox = dtk.GroupBox(context, "Push Buttons", layout)
hLayout = dtk.HorizontalLayout(context, groupBox)
pushButton = dtk.PushButton(context, "Click", hLayout)
pushButton.setClickedCallback(lambda: print("Click"))
pushButton = dtk.PushButton(context, "Text", hLayout)
pushButton.icon = "Settings"
pushButton = dtk.PushButton(context, "Disabled", hLayout)
pushButton.enabled = False
        
# Create tool buttons.
groupBox = dtk.GroupBox(context, "Tool Buttons", layout)
hLayout = dtk.HorizontalLayout(context, groupBox)
toolButtonGroup = dtk.ButtonGroup(context, dtk.ButtonGroupType.Radio)
toolButtonGroup.setCheckedCallback(lambda index, checked: print("Tool:", index))
hLayout = dtk.HorizontalLayout(context, groupBox)
toolIcons = [
    "PlaybackReverse",
    "PlaybackStop",
    "PlaybackForward"
]
hLayout2 = dtk.HorizontalLayout(context, hLayout)
hLayout2.spacingRole = dtk.SizeRole.SizeRole_None
for i in range(0, 3):
    toolButton = dtk.ToolButton(context, hLayout2)
    toolButton.checkable = True
    toolButton.checked = 0 == i
    toolButton.icon = toolIcons[i]
    toolButtonGroup.addButton(toolButton)
toolButton = dtk.ToolButton(context, "Text", hLayout)
toolButton = dtk.ToolButton(context, "Text", hLayout)
toolButton.icon = "Settings"
toolButton = dtk.ToolButton(context, "Disabled", hLayout)
toolButton.enabled = False
toolButtonGroup.addButton(toolButton)

# Create check boxes.
groupBox = dtk.GroupBox(context, "Check Boxes", layout)
vLayout = dtk.VerticalLayout(context, groupBox)
checkBox = dtk.CheckBox(context, "Checkable", vLayout)
checkBox.setCheckedCallback(lambda checked: print("Checked:", checked))
checkBox = dtk.CheckBox(context, "Disabled", vLayout)
checkBox.enabled = False

window.show()
app.run()
# \bug Need to manually reset the window.
window = None
