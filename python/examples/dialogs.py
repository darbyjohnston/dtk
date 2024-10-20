# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

import dtk

import sys
    
context = dtk.Context()
app = dtk.App(context, sys.argv, "buttons", "Buttons example")
if app.getExit() != 0:
    sys.exit(1)

# Disable the native file dialog.
for system in context.systems:
    if isinstance(system, dtk.FileBrowserSystem):
        system.nativeFileDialog = False

# Create the window.
window = dtk.Window(context, "buttons", dtk.Size2I(1280, 960))
app.addWindow(window)

# Create the layout.
layout = dtk.VerticalLayout(context)
layout.marginRole = dtk.SizeRole.Margin
scrollWidget = dtk.ScrollWidget(context, dtk.ScrollType.Both, window)
scrollWidget.widget = layout

# Message dialog.
button = dtk.PushButton(context, "Message Dialog", layout)
button.setClickedCallback(
    lambda: context.getSystemByName("dtk::DialogSystem").message("Message", "Hello world!", window))

# Confirmation dialog.
button = dtk.PushButton(context, "Confirmation Dialog", layout)
button.setClickedCallback(lambda: context.getSystemByName("dtk::DialogSystem").
        confirm("Confirm", "Hello world?", window, lambda ok: print("Hellow world:", ok)))

# File browser.
fileEdit = dtk.FileEdit(context, layout)
fileEdit.path = "File Browser"

window.show()
app.run()
# \bug Need to manually reset the window.
window = None
