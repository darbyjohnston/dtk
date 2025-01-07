set(HEADERS Resource.h)

set(SOURCE
    Resource.cpp
    ../../../etc/Fonts/NotoSans-Bold.cpp
    ../../../etc/Fonts/NotoSans-Regular.cpp
    ../../../etc/Fonts/NotoSansMono-Regular.cpp
    ../../../etc/Icons/ArrowDown.cpp
    ../../../etc/Icons/ArrowLeft.cpp
    ../../../etc/Icons/ArrowRight.cpp
    ../../../etc/Icons/ArrowUp.cpp
    ../../../etc/Icons/Audio.cpp
    ../../../etc/Icons/BellowsClosed.cpp
    ../../../etc/Icons/BellowsOpen.cpp
    ../../../etc/Icons/Clear.cpp
    ../../../etc/Icons/Close.cpp
    ../../../etc/Icons/Copy.cpp
    ../../../etc/Icons/Decrement.cpp
    ../../../etc/Icons/Directory.cpp
    ../../../etc/Icons/DirectoryBack.cpp
    ../../../etc/Icons/DirectoryForward.cpp
    ../../../etc/Icons/DirectoryUp.cpp
    ../../../etc/Icons/Edit.cpp
    ../../../etc/Icons/Empty.cpp
    ../../../etc/Icons/File.cpp
    ../../../etc/Icons/FileBrowser.cpp
    ../../../etc/Icons/FileClose.cpp
    ../../../etc/Icons/FileCloseAll.cpp
    ../../../etc/Icons/FileOpen.cpp
    ../../../etc/Icons/FrameEnd.cpp
    ../../../etc/Icons/FrameInOut.cpp
    ../../../etc/Icons/FrameNext.cpp
    ../../../etc/Icons/FramePrev.cpp
    ../../../etc/Icons/FrameStart.cpp
    ../../../etc/Icons/Increment.cpp
    ../../../etc/Icons/MenuArrow.cpp
    ../../../etc/Icons/MenuChecked.cpp
    ../../../etc/Icons/Mute.cpp
    ../../../etc/Icons/Next.cpp
    ../../../etc/Icons/PanelBottom.cpp
    ../../../etc/Icons/PanelLeft.cpp
    ../../../etc/Icons/PanelRight.cpp
    ../../../etc/Icons/PanelTop.cpp
    ../../../etc/Icons/PlaybackForward.cpp
    ../../../etc/Icons/PlaybackReverse.cpp
    ../../../etc/Icons/PlaybackStop.cpp
    ../../../etc/Icons/Prev.cpp
    ../../../etc/Icons/Reload.cpp
    ../../../etc/Icons/Reset.cpp
    ../../../etc/Icons/ReverseSort.cpp
    ../../../etc/Icons/Search.cpp
    ../../../etc/Icons/Settings.cpp
    ../../../etc/Icons/SubMenuArrow.cpp
    ../../../etc/Icons/TimeEnd.cpp
    ../../../etc/Icons/TimeStart.cpp
    ../../../etc/Icons/ViewFrame.cpp
    ../../../etc/Icons/ViewZoomIn.cpp
    ../../../etc/Icons/ViewZoomOut.cpp
    ../../../etc/Icons/ViewZoomReset.cpp
    ../../../etc/Icons/Volume.cpp
    ../../../etc/Icons/WindowFullScreen.cpp)

add_library(dtkResource ${HEADERS} ${SOURCE})
target_link_libraries(dtkResource)
set_target_properties(dtkResource PROPERTIES FOLDER lib)

install(
    TARGETS dtkResource
    EXPORT dtkResourceTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/dtk/ui)
install(
    EXPORT dtkResourceTargets
    FILE dtkResourceTargets.cmake
    DESTINATION "lib/cmake/dtk"
    NAMESPACE dtk::)
