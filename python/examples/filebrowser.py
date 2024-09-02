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
        
# Create the file widgets.
for i in range(0, 10):
    dtk.FileEdit(context, layout)

window.show()
app.run()
# \bug Need to manually reset the window.
window = None
