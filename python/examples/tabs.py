# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

import dtk

import sys
        
context = dtk.Context()
app = dtk.App(context, sys.argv, "tabs", "Tabs example")
if app.getExit() != 0:
    sys.exit(1)

# Create the window.
window = dtk.MainWindow(context, app, "tabs", dtk.Size2I(1280, 960))
app.addWindow(window)

# Create the tab widget.
tabWidget = dtk.TabWidget(context)
tabWidget.vStretch = dtk.Stretch.Expanding
window.setWidget(tabWidget)

# Add tabs.
for i in range(0, 10):
    label = dtk.Label(context, dtk.getLoremIpsum(100))
    label.marginRole = dtk.SizeRole.MarginSmall
    scrollWidget = dtk.ScrollWidget(context)
    scrollWidget.border = False
    scrollWidget.widget = label
    tabWidget.addTab("Tab {}".format(i), scrollWidget)

window.show()
app.run()
# \bug Need to manually reset the window.
window = None
