# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

from dtk import *

import sys
        
context = dtkCore.Context()
app = dtkUI.App(context, sys.argv, "buttons", "Buttons example")
if app.getExit() != 0:
    sys.exit(1)

# Disable the native file dialog.
for system in context.systems:
    if isinstance(system, dtkUI.FileBrowserSystem):
        system.nativeFileDialog = False

# Create the window.
window = dtkUI.Window(context, "buttons", dtkCore.Size2I(1280, 960))
app.addWindow(window)

# Create the layout.
layout = dtkUI.VerticalLayout(context)
layout.marginRole = dtkUI.SizeRole.Margin
scrollWidget = dtkUI.ScrollWidget(context, dtkUI.ScrollType.Both, window)
scrollWidget.widget = layout
        
# Create the file widgets.
for i in range(0, 10):
    dtkUI.FileEdit(context, layout)

window.show()
app.run()
# \bug Need to manually reset the window.
window = None
