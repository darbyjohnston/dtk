add_subdirectory(coreTest)
add_subdirectory(testLib)
add_subdirectory(uiTest)
add_subdirectory(dtktest)
if ("${dtk_API}" STREQUAL "GL_4_1" OR
    "${dtk_API}" STREQUAL "GL_4_1_Debug" OR
    "${dtk_API}" STREQUAL "GLES_2")
    add_subdirectory(glTest)
endif()
