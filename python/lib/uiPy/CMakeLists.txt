set(HEADERS
    App.h
    Bellows.h
    Bindings.h
    ButtonGroup.h
    CheckBox.h
    ColorPopup.h
    ColorSwatch.h
    ColorWidget.h
    DoubleEdit.h
    DoubleEditSlider.h
    DoubleModel.h
    DoubleSlider.h
    Event.h
    FileBrowser.h
    FileEdit.h
    FloatEdit.h
    FloatEditSlider.h
    FloatModel.h
    FloatSlider.h
    GroupBox.h
    IButton.h
    IPopup.h
    IWidget.h
    IWidgetPopup.h
    IWindow.h
    IntEdit.h
    IntEditSlider.h
    IntModel.h
    IntSlider.h
    MDICanvas.h
    MDIWidget.h
    PushButton.h
    RecentFilesModel.h
    RowLayout.h
    ScrollArea.h
    ScrollWidget.h
    Style.h
    TabBar.h
    TabWidget.h
    ToolButton.h
    WidgetOptions.h
    Window.h)
set(HEADERS_PRIVATE)
set(SOURCE
    App.cpp
    Bellows.cpp
    Bindings.cpp
    ButtonGroup.cpp
    CheckBox.cpp
    ColorPopup.cpp
    ColorSwatch.cpp
    ColorWidget.cpp
    DoubleEdit.cpp
    DoubleEditSlider.cpp
    DoubleModel.cpp
    DoubleSlider.cpp
    Event.cpp
    FileBrowser.cpp
    FloatEdit.cpp
    FloatEditSlider.cpp
    FloatModel.cpp
    FloatSlider.cpp
    FileEdit.cpp
    GroupBox.cpp
    IButton.cpp
    IPopup.cpp
    IWidget.cpp
    IWidgetPopup.cpp
    IWindow.cpp
    IntEdit.cpp
    IntEditSlider.cpp
    IntModel.cpp
    IntSlider.cpp
    MDICanvas.cpp
    MDIWidget.cpp
    PushButton.cpp
    RecentFilesModel.cpp
    RowLayout.cpp
    ScrollArea.cpp
    ScrollWidget.cpp
    Style.cpp
    TabBar.cpp
    TabWidget.cpp
    ToolButton.cpp
    WidgetOptions.cpp
    Window.cpp)

add_library(dtkUIPy ${HEADERS} ${HEADERS_PRIVATE} ${SOURCE})
target_link_libraries(dtkUIPy dtkUI Python3::Python)
set_target_properties(dtkUIPy PROPERTIES FOLDER python/lib)
set_target_properties(dtkUIPy PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS dtkUIPy
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/dtk/dtkUIPy)
