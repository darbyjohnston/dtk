# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

import feather_tk as ftk

import sys

# Create the context and application.
context = ftk.Context()
app = ftk.App(context, sys.argv, "tabs", "Tabs example")
if app.getExit() != 0:
    sys.exit(1)

# Create a window.
window = ftk.MainWindow(context, app, "tabs", ftk.Size2I(1280, 960))

# Create a tab widget.
tabWidget = ftk.TabWidget(context)
tabWidget.vStretch = ftk.Stretch.Expanding
window.setWidget(tabWidget)

# Add tabs.
for i in range(0, 10):
    label = ftk.Label(context, ftk.getLoremIpsum(100))
    label.marginRole = ftk.SizeRole.MarginSmall
    scrollWidget = ftk.ScrollWidget(context)
    scrollWidget.border = False
    scrollWidget.widget = label
    tabWidget.addTab("Tab {}".format(i), scrollWidget)

# Show the window and run the application.
window.show()
app.run()

# \bug Need to manually reset the window.
window = None
