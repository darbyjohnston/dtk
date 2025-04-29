# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

import dtk

import sys
    
context = dtk.Context()
app = dtk.App(context, sys.argv, "simple", "Simple example")
if app.getExit() != 0:
    sys.exit(app.getExit())

window = dtk.MainWindow(context, app, "simple", dtk.Size2I(1280, 960))
app.addWindow(window)

label = dtk.Label(context, "Hello world")
label.setAlign(dtk.HAlign.Center, dtk.VAlign.Center);
label.setStretch(dtk.Stretch.Expanding);
window.setWidget(label)

window.show()
app.run()
# \bug Need to manually reset the window.
window = None
