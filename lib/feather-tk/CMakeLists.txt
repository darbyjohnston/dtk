add_subdirectory(core)
add_subdirectory(resource)
if(feather_tk_UI_LIB)
    if ("${feather_tk_API}" STREQUAL "GL_4_1" OR
        "${feather_tk_API}" STREQUAL "GL_4_1_Debug" OR
        "${feather_tk_API}" STREQUAL "GLES_2")
        add_subdirectory(gl)
    endif()
    add_subdirectory(ui)
endif()
