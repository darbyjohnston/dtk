// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiPy/Bindings.h>

#include <uiPy/App.h>
#include <uiPy/Bellows.h>
#include <uiPy/ButtonGroup.h>
#include <uiPy/CheckBox.h>
#include <uiPy/ColorPopup.h>
#include <uiPy/ColorSwatch.h>
#include <uiPy/ColorWidget.h>
#include <uiPy/ConfirmDialog.h>
#include <uiPy/DialogSystem.h>
#include <uiPy/DoubleEdit.h>
#include <uiPy/DoubleEditSlider.h>
#include <uiPy/DoubleModel.h>
#include <uiPy/DoubleSlider.h>
#include <uiPy/Event.h>
#include <uiPy/FileBrowser.h>
#include <uiPy/FileEdit.h>
#include <uiPy/FloatEdit.h>
#include <uiPy/FloatEditSlider.h>
#include <uiPy/FloatModel.h>
#include <uiPy/FloatSlider.h>
#include <uiPy/GridLayout.h>
#include <uiPy/GroupBox.h>
#include <uiPy/IButton.h>
#include <uiPy/IDialog.h>
#include <uiPy/IPopup.h>
#include <uiPy/IWidget.h>
#include <uiPy/IWidgetPopup.h>
#include <uiPy/IWindow.h>
#include <uiPy/Icon.h>
#include <uiPy/IconSystem.h>
#include <uiPy/IntEdit.h>
#include <uiPy/IntEditSlider.h>
#include <uiPy/IntModel.h>
#include <uiPy/IntSlider.h>
#include <uiPy/Label.h>
#include <uiPy/MDICanvas.h>
#include <uiPy/MDIWidget.h>
#include <uiPy/MessageDialog.h>
#include <uiPy/ProgressDialog.h>
#include <uiPy/PushButton.h>
#include <uiPy/RecentFilesModel.h>
#include <uiPy/RowLayout.h>
#include <uiPy/ScrollArea.h>
#include <uiPy/ScrollWidget.h>
#include <uiPy/Settings.h>
#include <uiPy/Style.h>
#include <uiPy/TabBar.h>
#include <uiPy/TabWidget.h>
#include <uiPy/ToolButton.h>
#include <uiPy/WidgetOptions.h>
#include <uiPy/Window.h>

#include <dtk/ui/Init.h>
#include <dtk/ui/Settings.h>

#include <dtk/core/Context.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace dtk
{
    void uiBind(py::module_& m)
    {
        m.def(
            "uiInit",
            &uiInit,
            py::arg("context"),
            py::arg("settings") = nullptr,
            "Initialize the library.");

        style(m);
        event(m);
        widgetOptions(m);
        iWidget(m);
        iWindow(m);
        iPopup(m);
        iDialog(m);
        iWidgetPopup(m);
        iButton(m);
        settings(m);

        app(m);
        bellows(m);
        buttonGroup(m);
        checkBox(m);
        colorPopup(m);
        colorSwatch(m);
        colorWidget(m);
        confirmDialog(m);
        dialogSystem(m);
        doubleEdit(m);
        doubleEditSlider(m);
        doubleModel(m);
        doubleSlider(m);
        fileBrowser(m);
        fileEdit(m);
        floatEdit(m);
        floatEditSlider(m);
        floatModel(m);
        floatSlider(m);
        gridLayout(m);
        groupBox(m);
        icon(m);
        iconSystem(m);
        intEdit(m);
        intEditSlider(m);
        intModel(m);
        intSlider(m);
        label(m);
        mdiCanvas(m);
        mdiWidget(m);
        messageDialog(m);
        progressDialog(m);
        pushButton(m);
        recentFilesModel(m);
        rowLayout(m);
        scrollArea(m);
        scrollWidget(m);
        tabBar(m);
        tabWidget(m);
        toolButton(m);
        window(m);
    }
}
