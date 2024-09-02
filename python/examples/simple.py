# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

import dtk

import sys

class Window(dtk.Window):
    def __init__(self, context, name, size):
        dtk.Window.__init__(self, context, name, size)
    
    def drawEvent(self, drawRect, event):
        dtk.Window.drawEvent(self, drawRect, event)
        
        text = "Hello world"
        fontInfo = dtk.FontInfo()
        fontInfo.size = 0
        textSize = dtk.Size2I()
        g = dtk.margin(self.geometry, -100)
        while textSize.w < g.w and textSize.h < g.h:
            fontInfo.size += 10
            textSize = event.fontSystem.getSize(text, fontInfo)
        glyphs = event.fontSystem.getGlyphs(text, fontInfo)
        fontMetrics = event.fontSystem.getMetrics(fontInfo)
        event.render.drawText(
            glyphs,
            fontMetrics,
            dtk.convert(dtk.center(g) - dtk.V2I(textSize.w, textSize.h) / 2),
            dtk.Color4F(1, 1, 1))
    
context = dtk.Context()
app = dtk.App(context, sys.argv, "simple", "Simple example")
if app.getExit() != 0:
    sys.exit(app.getExit())
window = Window(context, "simple", dtk.Size2I(1280, 960))
app.addWindow(window)
window.show()
app.run()
# \bug Need to manually reset the window.
window = None
