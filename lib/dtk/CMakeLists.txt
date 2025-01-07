add_subdirectory(core)
add_subdirectory(resource)
if(dtk_UI_LIB)
    if ("${dtk_API}" STREQUAL "GL_4_1" OR
        "${dtk_API}" STREQUAL "GL_4_1_Debug" OR
        "${dtk_API}" STREQUAL "GLES_2")
        add_subdirectory(gl)
    endif()
    add_subdirectory(ui)
endif()
