# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

import dtk

import sys

class DialogsWindow(dtk.MainWindow):
    def __init__(self, context, app, name, size):
        dtk.MainWindow.__init__(self, context, app, name, size)
        
        # Create the layout.
        layout = dtk.VerticalLayout(context)
        layout.marginRole = dtk.SizeRole.Margin
        self.setWidget(layout)

        # Message dialog.
        button = dtk.PushButton(context, "Message Dialog", layout)
        button.setClickedCallback(
            lambda: context.getSystemByName("dtk::DialogSystem").message("Message", "Hello world!", window))

        # Confirmation dialog.
        button = dtk.PushButton(context, "Confirmation Dialog", layout)
        button.setClickedCallback(lambda: context.getSystemByName("dtk::DialogSystem").
            confirm("Confirm", "Hello world?", window, lambda ok: print("Hellow world:", ok)))

        # Progress dialog.
        self.progressTimer = dtk.Timer(context)
        self.progressTimer.repeating = True
        button = dtk.PushButton(context, "Progress Dialog", layout)
        button.setClickedCallback(self._progressDialog)

        # File browser.
        fileEdit = dtk.FileEdit(context, layout)
        fileEdit.path = "File Browser"        

    def _progressDialog(self):
        self.progressDialog = dtk.ProgressDialog(self.context, "Progress", "In progress:", self)
        self.progressDialog.setCloseCallback(self._progressDialogClose)
        self.progressDialog.show()
        self.progressTimer.start(0.5, self._progressTimerCallback)

    def _progressDialogClose(self):
        self.progressTimer.stop()
        self.progressDialog = None

    def _progressTimerCallback(self):
        v = self.progressDialog.value
        v += 0.005
        if v < 1.0:
            self.progressDialog.value = v
        else:
            self.progressDialog.close()

context = dtk.Context()
app = dtk.App(context, sys.argv, "dialogs", "Dialogs example")
if app.getExit() != 0:
    sys.exit(1)

# Disable the native file dialog.
context.getSystemByName("dtk::FileBrowserSystem").nativeFileDialog = False

# Create the window.
window = DialogsWindow(context, app, "dialogs", dtk.Size2I(1280, 960))
app.addWindow(window)

window.show()
app.run()
# \bug Need to manually reset the window.
window = None
