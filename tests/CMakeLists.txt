add_subdirectory(coreTest)
add_subdirectory(dtktest)
add_subdirectory(testLib)
if(dtk_UI_LIB)
    if ("${dtk_API}" STREQUAL "GL_4_1" OR
        "${dtk_API}" STREQUAL "GL_4_1_Debug" OR
        "${dtk_API}" STREQUAL "GLES_2")
        add_subdirectory(glTest)
    endif()
    add_subdirectory(uiTest)
endif()
