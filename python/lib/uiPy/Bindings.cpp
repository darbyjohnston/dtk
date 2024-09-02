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
#include <uiPy/GroupBox.h>
#include <uiPy/IButton.h>
#include <uiPy/IntEdit.h>
#include <uiPy/IntEditSlider.h>
#include <uiPy/IntModel.h>
#include <uiPy/IntSlider.h>
#include <uiPy/IPopup.h>
#include <uiPy/IWidget.h>
#include <uiPy/IWidgetPopup.h>
#include <uiPy/IWindow.h>
#include <uiPy/MDICanvas.h>
#include <uiPy/MDIWidget.h>
#include <uiPy/PushButton.h>
#include <uiPy/RecentFilesModel.h>
#include <uiPy/RowLayout.h>
#include <uiPy/ScrollArea.h>
#include <uiPy/ScrollWidget.h>
#include <uiPy/Style.h>
#include <uiPy/TabBar.h>
#include <uiPy/TabWidget.h>
#include <uiPy/ToolButton.h>
#include <uiPy/WidgetOptions.h>
#include <uiPy/Window.h>

#include <dtk/ui/Init.h>

#include <dtk/core/Context.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace dtk
{
    namespace ui
    {
        void bind(py::module_& m)
        {
            auto sm = m.def_submodule("dtkUI");
            sm.doc() = "User interface";

            sm.def("init", &init, "Initialize the library.");

            style(sm);
            event(sm);
            widgetOptions(sm);
            iWidget(sm);
            iWindow(sm);
            iPopup(sm);
            iWidgetPopup(sm);
            iButton(sm);

            app(sm);
            bellows(sm);
            buttonGroup(sm);
            checkBox(sm);
            colorPopup(sm);
            colorSwatch(sm);
            colorWidget(sm);
            doubleEdit(sm);
            doubleEditSlider(sm);
            doubleModel(sm);
            doubleSlider(sm);
            fileBrowser(sm);
            fileEdit(sm);
            floatEdit(sm);
            floatEditSlider(sm);
            floatModel(sm);
            floatSlider(sm);
            groupBox(sm);
            intEdit(sm);
            intEditSlider(sm);
            intModel(sm);
            intSlider(sm);
            mdiCanvas(sm);
            mdiWidget(sm);
            pushButton(sm);
            recentFilesModel(sm);
            rowLayout(sm);
            scrollArea(sm);
            scrollWidget(sm);
            tabBar(sm);
            tabWidget(sm);
            toolButton(sm);
            window(sm);
        }
    }
}
