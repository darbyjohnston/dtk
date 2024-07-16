add_subdirectory(dtkBaseApp)
add_subdirectory(dtkCore)
add_subdirectory(dtkResourceApp)
add_subdirectory(dtkUI)
add_subdirectory(dtkUIApp)
if ("${dtk_API}" STREQUAL "GL_4_1" OR
    "${dtk_API}" STREQUAL "GL_4_1_Debug" OR
    "${dtk_API}" STREQUAL "GLES_2")
    add_subdirectory(dtkGL)
endif()

