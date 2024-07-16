set(HEADERS
    App.h
    Window.h)
set(PRIVATE_HEADERS)

set(SOURCE)
if ("${dtk_API}" STREQUAL "GL_4_1" OR
    "${dtk_API}" STREQUAL "GL_4_1_Debug" OR
    "${dtk_API}" STREQUAL "GLES_2")
    list(APPEND SOURCE
        AppGL.cpp
        WindowGL.cpp)
endif()

set(LIBRARIES)
if ("${dtk_API}" STREQUAL "GL_4_1" OR
    "${dtk_API}" STREQUAL "GL_4_1_Debug" OR
    "${dtk_API}" STREQUAL "GLES_2")
    list(APPEND LIBRARIES dtkGL)
endif()
list(APPEND LIBRARIES dtkUI dtkBaseApp)

add_library(dtkUIApp ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(dtkUIApp ${LIBRARIES})
set_target_properties(dtkUIApp PROPERTIES FOLDER lib)
set_target_properties(dtkUIApp PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS dtkUIApp
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/dtk/dtkUIApp)

