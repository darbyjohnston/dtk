set(HEADERS
    GL.h
    Init.h
    Mesh.h
    OffscreenBuffer.h
    Render.h
    Shader.h
    System.h
    Texture.h
    TextureAtlas.h
    Util.h
    Window.h)
set(PRIVATE_HEADERS
    RenderPrivate.h)

set(SOURCE
    Init.cpp
    Mesh.cpp
    Mesh.cpp
    OffscreenBuffer.cpp
    Render.cpp
    RenderPrims.cpp
    Shader.cpp
    System.cpp
    Texture.cpp
    TextureAtlas.cpp
    Util.cpp
    Window.cpp)
if ("${dtk_API}" STREQUAL "GL_4_1" OR
    "${dtk_API}" STREQUAL "GL_4_1_Debug")
    list(APPEND SOURCE RenderShaders_GL_4_1.cpp)
elseif ("${dtk_API}" STREQUAL "GLES_2")
    list(APPEND SOURCE RenderShaders_GLES_2.cpp)
endif()

add_library(dtkGL ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(dtkGL dtkCore glad glfw)
set_target_properties(dtkGL PROPERTIES FOLDER lib)
set_target_properties(dtkGL PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(
    TARGETS dtkGL
    EXPORT dtkGLTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/dtk/gl)
install(
    EXPORT dtkGLTargets
    FILE dtkGLTargets.cmake
    DESTINATION "share/dtk"
    NAMESPACE dtk::)
