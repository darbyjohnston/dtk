add_subdirectory(core)
add_subdirectory(ui)
if ("${dtk_API}" STREQUAL "GL_4_1" OR
    "${dtk_API}" STREQUAL "GL_4_1_Debug" OR
    "${dtk_API}" STREQUAL "GLES_2")
    add_subdirectory(gl)
endif()
