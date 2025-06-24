# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

import feather_tk as ftk

import sys

class DialogsWindow(ftk.MainWindow):
    def __init__(self, context, app, name, size):
        ftk.MainWindow.__init__(self, context, app, name, size)
        
        # Create a layout.
        layout = ftk.VerticalLayout(context)
        layout.marginRole = ftk.SizeRole.Margin
        self.setWidget(layout)

        # Message dialog.
        button = ftk.PushButton(context, "Message Dialog", layout)
        button.setClickedCallback(
            lambda: context.getSystemByName("feather_tk::DialogSystem").message("Message", "Hello world!", window))

        # Confirmation dialog.
        button = ftk.PushButton(context, "Confirmation Dialog", layout)
        button.setClickedCallback(lambda: context.getSystemByName("feather_tk::DialogSystem").
            confirm("Confirm", "Hello world?", window, lambda ok: print("Hellow world:", ok)))

        # Progress dialog.
        self.progressTimer = ftk.Timer(context)
        self.progressTimer.repeating = True
        button = ftk.PushButton(context, "Progress Dialog", layout)
        button.setClickedCallback(self._progressDialog)

        # File browsers.
        fileEdit = ftk.FileEdit(context, layout)
        fileEdit.path = "File Browser"
        dirEdit = ftk.FileEdit(context, ftk.FileBrowserMode.Dir, layout)
        dirEdit.path = "Directory Browser"

    def _progressDialog(self):
        self.progressDialog = ftk.ProgressDialog(self.context, "Progress", "In progress:", self)
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

# Create the context and application.
context = ftk.Context()
app = ftk.App(context, sys.argv, "dialogs", "Dialogs example")
if app.getExit() != 0:
    sys.exit(1)

# Disable the native file dialog.
context.getSystemByName("feather_tk::FileBrowserSystem").nativeFileDialog = False

# Create a window.
window = DialogsWindow(context, app, "dialogs", ftk.Size2I(1280, 960))

# Show the window and run the application.
window.show()
app.run()

# \bug Need to manually reset the window.
window = None
