set(HEADERS
    MeshTest.h
    OffscreenBufferTest.h
    RenderTest.h
    ShaderTest.h
    TextureAtlasTest.h
    TextureTest.h
    WindowTest.h)
set(PRIVATE_HEADERS)

set(SOURCE
    MeshTest.cpp
    OffscreenBufferTest.cpp
    RenderTest.cpp
    ShaderTest.cpp
    TextureAtlasTest.cpp
    TextureTest.cpp
    WindowTest.cpp)

add_library(dtkGLTest ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(dtkGLTest dtkGL dtkTestLib)
set_target_properties(dtkGLTest PROPERTIES FOLDER tests)
set_target_properties(dtkGLTest PROPERTIES PUBLIC_HEADER "${HEADERS}")

