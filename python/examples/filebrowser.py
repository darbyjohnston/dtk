# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

from tinygfx import *

import sys
        
context = tgCore.Context()
app = tgUIApp.App(context, sys.argv, "buttons", "Buttons example")
if app.getExit() != 0:
    sys.exit(1)

# Disable the native file dialog.
for system in context.systems:
    if isinstance(system, tgUI.FileBrowserSystem):
        system.nativeFileDialog = False

# Create the window.
window = tgUIApp.Window(context, "buttons", tgCore.Size2I(1280, 960))
app.addWindow(window)

# Create the layout.
layout = tgUI.VerticalLayout(context)
layout.marginRole = tgUI.SizeRole.Margin
scrollWidget = tgUI.ScrollWidget(context, tgUI.ScrollType.Both, window)
scrollWidget.widget = layout
        
# Create the file widgets.
for i in range(0, 10):
    tgUI.FileEdit(context, layout)

window.show()
app.run()
# \bug Need to manually reset the window.
window = None
