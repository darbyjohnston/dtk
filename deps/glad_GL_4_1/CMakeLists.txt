set(HEADERS
    include/glad/gl.h
    include/KHR/khrplatform.h)

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
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/dtk"
    NAMESPACE dtk::)

install(
    DIRECTORY
    "${CMAKE_CURRENT_SOURCE_DIR}/include/glad"
    DESTINATION "include/tinygfx")
install(
    DIRECTORY
    "${CMAKE_CURRENT_SOURCE_DIR}/include/KHR"
    DESTINATION "include/tinygfx")
