# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

from dtk import *

import sys

class Window(dtkUI.Window):
    def __init__(self, context, name, size):
        dtkUI.Window.__init__(self, context, name, size)
    
    def drawEvent(self, drawRect, event):
        dtkUI.Window.drawEvent(self, drawRect, event)
        
        text = "Hello world"
        fontInfo = dtkCore.FontInfo()
        fontInfo.size = 0
        textSize = dtkCore.Size2I()
        g = dtkCore.margin(self.geometry, -100)
        while textSize.w < g.w and textSize.h < g.h:
            fontInfo.size += 10
            textSize = event.fontSystem.getSize(text, fontInfo)
        glyphs = event.fontSystem.getGlyphs(text, fontInfo)
        fontMetrics = event.fontSystem.getMetrics(fontInfo)
        event.render.drawText(
            glyphs,
            fontMetrics,
            dtkCore.convert(dtkCore.center(g) - dtkCore.V2I(textSize.w, textSize.h) / 2),
            dtkCore.Color4F(1, 1, 1))
    
context = dtkCore.Context()
app = dtkUI.App(context, sys.argv, "simple", "Simple example")
if app.getExit() != 0:
    sys.exit(app.getExit())
window = Window(context, "simple", dtkCore.Size2I(1280, 960))
app.addWindow(window)
window.show()
app.run()
# \bug Need to manually reset the window.
window = None
