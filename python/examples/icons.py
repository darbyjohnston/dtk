# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

import dtk

import sys

context = dtk.Context()
app = dtk.App(context, sys.argv, "icons", "Icons example")
if app.getExit() != 0:
    sys.exit(app.getExit())

# Create the window.
window = dtk.Window(context, "icons", dtk.Size2I(1280, 960))
app.addWindow(window)

# Create the layout.
layout = dtk.GridLayout(context)
layout.marginRole = dtk.SizeRole.MarginSmall
layout.spacingRole = dtk.SizeRole.SpacingSmall
scrollWidget = dtk.ScrollWidget(context, dtk.ScrollType.Both, window)
scrollWidget.widget = layout
        
# Create the icons.

window.show()
app.run()
# \bug Need to manually reset the window.
window = None
