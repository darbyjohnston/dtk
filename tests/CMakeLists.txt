add_subdirectory(dtkBaseAppTest)
add_subdirectory(dtkCoreTest)
add_subdirectory(dtkTestLib)
add_subdirectory(dtkUITest)
add_subdirectory(dtktest)
if ("${dtk_API}" STREQUAL "GL_4_1" OR
    "${dtk_API}" STREQUAL "GL_4_1_Debug" OR
    "${dtk_API}" STREQUAL "GLES_2")
    add_subdirectory(dtkGLTest)
    add_subdirectory(dtkUIAppTest)
endif()
