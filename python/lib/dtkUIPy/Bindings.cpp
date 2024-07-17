// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkUIPy/Bindings.h>

#include <dtkUIPy/Bellows.h>
#include <dtkUIPy/ButtonGroup.h>
#include <dtkUIPy/CheckBox.h>
#include <dtkUIPy/ColorPopup.h>
#include <dtkUIPy/ColorSwatch.h>
#include <dtkUIPy/ColorWidget.h>
#include <dtkUIPy/DoubleEdit.h>
#include <dtkUIPy/DoubleEditSlider.h>
#include <dtkUIPy/DoubleModel.h>
#include <dtkUIPy/DoubleSlider.h>
#include <dtkUIPy/Event.h>
#include <dtkUIPy/FileBrowser.h>
#include <dtkUIPy/FileEdit.h>
#include <dtkUIPy/FloatEdit.h>
#include <dtkUIPy/FloatEditSlider.h>
#include <dtkUIPy/FloatModel.h>
#include <dtkUIPy/FloatSlider.h>
#include <dtkUIPy/GroupBox.h>
#include <dtkUIPy/IButton.h>
#include <dtkUIPy/IntEdit.h>
#include <dtkUIPy/IntEditSlider.h>
#include <dtkUIPy/IntModel.h>
#include <dtkUIPy/IntSlider.h>
#include <dtkUIPy/IPopup.h>
#include <dtkUIPy/IWidget.h>
#include <dtkUIPy/IWidgetPopup.h>
#include <dtkUIPy/IWindow.h>
#include <dtkUIPy/MDICanvas.h>
#include <dtkUIPy/MDIWidget.h>
#include <dtkUIPy/PushButton.h>
#include <dtkUIPy/RecentFilesModel.h>
#include <dtkUIPy/RowLayout.h>
#include <dtkUIPy/ScrollArea.h>
#include <dtkUIPy/ScrollWidget.h>
#include <dtkUIPy/Style.h>
#include <dtkUIPy/TabBar.h>
#include <dtkUIPy/TabWidget.h>
#include <dtkUIPy/ToolButton.h>
#include <dtkUIPy/WidgetOptions.h>

#include <dtkUI/Init.h>

#include <dtkCore/Context.h>

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
        }
    }
}
