# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

import feather_tk as ftk
import sys

# Create the context and application.
context = ftk.Context()
app = ftk.App(context, sys.argv, "simple", "Simple example")
if app.getExit() != 0:
    sys.exit(app.getExit())

# Create a window.
window = ftk.MainWindow(context, app, "simple", ftk.Size2I(1280, 960))

# Create a label.
label = ftk.Label(context, "Hello world")
label.fontRole = ftk.FontRole.Title
label.setAlign(ftk.HAlign.Center, ftk.VAlign.Center)
label.setStretch(ftk.Stretch.Expanding)
window.setWidget(label)

# Show the window and run the application.
window.show()
app.run()

# \bug Need to manually reset the window.
window = None
