set(HEADERS
    feather-tk/glad/gl.h
    feather-tk/KHR/khrplatform.h)

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
    DESTINATION "share/feather-tk"
    NAMESPACE feather_tk::)
install(
    DIRECTORY
    "${CMAKE_CURRENT_SOURCE_DIR}/feather-tk/glad"
    DESTINATION "include/feather-tk")
install(
    DIRECTORY
    "${CMAKE_CURRENT_SOURCE_DIR}/feather-tk/KHR"
    DESTINATION "include/feather-tk")
