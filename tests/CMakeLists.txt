add_subdirectory(coreTest)
add_subdirectory(feather-tk-test)
add_subdirectory(testLib)
if(feather_tk_UI_LIB)
    if ("${feather_tk_API}" STREQUAL "GL_4_1" OR
        "${feather_tk_API}" STREQUAL "GL_4_1_Debug" OR
        "${feather_tk_API}" STREQUAL "GLES_2")
        add_subdirectory(glTest)
    endif()
    add_subdirectory(uiTest)
endif()
