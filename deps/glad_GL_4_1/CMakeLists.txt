set(HEADERS
    dtk/glad/gl.h
    dtk/KHR/khrplatform.h)

set(SOURCE
    src/gl.c)

add_library(glad ${HEADERS} ${SOURCE})
target_link_libraries(glad OpenGL::GL ${CMAKE_DL_LIBS})
set_target_properties(glad PROPERTIES FOLDER deps)

install(
    TARGETS glad
    EXPORT gladTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)
install(
    EXPORT gladTargets
    FILE gladTargets.cmake
    DESTINATION "lib/cmake/dtk"
    NAMESPACE dtk::)
install(
    DIRECTORY
    "${CMAKE_CURRENT_SOURCE_DIR}/dtk/glad"
    DESTINATION "include/dtk")
install(
    DIRECTORY
    "${CMAKE_CURRENT_SOURCE_DIR}/dtk/KHR"
    DESTINATION "include/dtk")
