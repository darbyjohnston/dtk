include(ExternalProject)

set(NFD_GIT_REPOSITORY "https://github.com/btzy/nativefiledialog-extended.git")
set(NFD_GIT_TAG "v1.2.1")

set(NFD_ARGS
    ${dtk_DEPS_ARGS}
    -DNFD_USE_ALLOWEDCONTENTTYPES_IF_AVAILABLE=OFF
    -DNFD_BUILD_TESTS=OFF)

ExternalProject_Add(
    NFD
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/NFD
    GIT_REPOSITORY ${NFD_GIT_REPOSITORY}
    GIT_TAG ${NFD_GIT_TAG}
    LIST_SEPARATOR |
    CMAKE_ARGS ${NFD_ARGS})
