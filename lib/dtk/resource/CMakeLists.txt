set(HEADERS)
set(SOURCE)
set(RESOURCES
    etc/Fonts/NotoSansBold.ttf
    etc/Fonts/NotoSansRegular.ttf
    etc/Fonts/NotoSansMonoRegular.ttf
    etc/Icons/ArrowDown.svg
    etc/Icons/ArrowLeft.svg
    etc/Icons/ArrowRight.svg
    etc/Icons/ArrowUp.svg
    etc/Icons/Audio.svg
    etc/Icons/BellowsClosed.svg
    etc/Icons/BellowsOpen.svg
    etc/Icons/Clear.svg
    etc/Icons/Close.svg
    etc/Icons/Copy.svg
    etc/Icons/Decrement.svg
    etc/Icons/Directory.svg
    etc/Icons/DirectoryBack.svg
    etc/Icons/DirectoryForward.svg
    etc/Icons/DirectoryUp.svg
    etc/Icons/Edit.svg
    etc/Icons/Empty.svg
    etc/Icons/File.svg
    etc/Icons/FileBrowser.svg
    etc/Icons/FileClose.svg
    etc/Icons/FileCloseAll.svg
    etc/Icons/FileOpen.svg
    etc/Icons/FrameEnd.svg
    etc/Icons/FrameInOut.svg
    etc/Icons/FrameNext.svg
    etc/Icons/FramePrev.svg
    etc/Icons/FrameStart.svg
    etc/Icons/Increment.svg
    etc/Icons/MenuArrow.svg
    etc/Icons/MenuChecked.svg
    etc/Icons/Mute.svg
    etc/Icons/Next.svg
    etc/Icons/PanelBottom.svg
    etc/Icons/PanelLeft.svg
    etc/Icons/PanelRight.svg
    etc/Icons/PanelTop.svg
    etc/Icons/PlaybackForward.svg
    etc/Icons/PlaybackReverse.svg
    etc/Icons/PlaybackStop.svg
    etc/Icons/Prev.svg
    etc/Icons/Reload.svg
    etc/Icons/Reset.svg
    etc/Icons/ReverseSort.svg
    etc/Icons/Search.svg
    etc/Icons/Settings.svg
    etc/Icons/SubMenuArrow.svg
    etc/Icons/TimeEnd.svg
    etc/Icons/TimeStart.svg
    etc/Icons/ViewFrame.svg
    etc/Icons/ViewZoomIn.svg
    etc/Icons/ViewZoomOut.svg
    etc/Icons/ViewZoomReset.svg
    etc/Icons/Volume.svg
    etc/Icons/WindowFullScreen.svg)
foreach(RESOURCE ${RESOURCES})
    get_filename_component(RESOURCE_BASE ${RESOURCE} NAME_WE)
    add_custom_command(
        OUTPUT ${CMAKE_SOURCE_DIR}/lib/dtk/resource/${RESOURCE_BASE}.h ${CMAKE_SOURCE_DIR}/lib/dtk/resource/${RESOURCE_BASE}.cpp
        COMMAND $<TARGET_FILE:dtkresource> ${CMAKE_SOURCE_DIR}/${RESOURCE} ${CMAKE_SOURCE_DIR}/lib/dtk/resource/${RESOURCE_BASE} dtk
        DEPENDS dtkresource)
    list(APPEND HEADERS ${CMAKE_SOURCE_DIR}/lib/dtk/resource/${RESOURCE_BASE}.h)
    list(APPEND SOURCE ${CMAKE_SOURCE_DIR}/lib/dtk/resource/${RESOURCE_BASE}.cpp)
endforeach()

add_library(dtkResource ${HEADERS} ${SOURCE})
target_link_libraries(dtkResource)
set_target_properties(dtkResource PROPERTIES FOLDER lib)
set_target_properties(dtkResource PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(
    TARGETS dtkResource
    EXPORT dtkResourceLibTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/dtk/resource)
install(
    EXPORT dtkResourceLibTargets
    FILE dtkResourceLibTargets.cmake
    DESTINATION "lib/cmake/dtk"
    NAMESPACE dtk::)
