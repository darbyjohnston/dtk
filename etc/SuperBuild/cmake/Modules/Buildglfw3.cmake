include(ExternalProject)

set(glfw3_GIT_REPOSITORY "https://github.com/glfw/glfw.git")
set(glfw3_GIT_TAG "3.4")

set(glfw3_PATCH
    ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/glfw3-patch/src/nsgl_context.m
    ${CMAKE_CURRENT_BINARY_DIR}/glfw3/src/glfw3/src/nsgl_context.m)
if(feather_tk_glfw3_DISABLE_MACOS_APP_DELEGATE)
    list(APPEND glfw3_PATCH
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw3-patch/src/cocoa_init.m
        ${CMAKE_CURRENT_BINARY_DIR}/glfw3/src/glfw3/src/cocoa_init.m)
endif()

set(glfw3_ARGS
    ${feather_tk_DEPS_ARGS}
    -DCMAKE_INSTALL_LIBDIR=lib
    -DGLFW_SHARED_LIBS=${BUILD_SHARED_LIBS}
    -DGLFW_BUILD_EXAMPLES=FALSE
    -DGLFW_BUILD_TESTS=FALSE
    -DGLFW_BUILD_DOCS=FALSE
    -DGLFW_BUILD_WAYLAND=${feather_tk_glfw3_Wayland})

ExternalProject_Add(
    glfw3
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/glfw3
    GIT_REPOSITORY ${glfw3_GIT_REPOSITORY}
    GIT_TAG ${glfw3_GIT_TAG}
    PATCH_COMMAND ${glfw3_PATCH}
    LIST_SEPARATOR |
    CMAKE_ARGS ${glfw3_ARGS})

