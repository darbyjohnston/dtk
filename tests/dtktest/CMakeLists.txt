set(HEADERS dtktest.h)

set(SOURCE dtktest.cpp)

set(LIBRARIES dtkCoreTest)
if(dtk_UI_LIB)
    if ("${dtk_API}" STREQUAL "GL_4_1" OR
        "${dtk_API}" STREQUAL "GL_4_1_Debug" OR
        "${dtk_API}" STREQUAL "GLES_2")
        list(APPEND LIBRARIES dtkGLTest)
    endif()
    list(APPEND LIBRARIES dtkUITest)
endif()

add_executable(dtktest ${SOURCE} ${HEADERS})
target_link_libraries(dtktest ${LIBRARIES})
set_target_properties(dtktest PROPERTIES FOLDER tests)

add_test(
    NAME dtktest
    COMMAND dtktest -log)
