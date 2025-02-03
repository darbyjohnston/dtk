cmake_minimum_required(VERSION 3.22)
cmake_policy(SET CMP0091 NEW)
cmake_policy(SET CMP0114 NEW)
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

project(
    dtk
    VERSION 0.1.0
    LANGUAGES CXX C)

#-------------------------------------------------------------------------------
# Options

set(dtk_UI_LIB ON CACHE BOOL "Build the user interface library")
set(dtk_API "GL_4_1" CACHE STRING "Graphics API (GL_4_1, GL_4_1_Debug, GLES_2)")
if(WIN32 OR APPLE)
    set(dtk_NFD_DEFAULT TRUE)
else()
    set(dtk_NFD_DEFAULT FALSE)
endif()
set(dtk_NFD ${dtk_NFD_DEFAULT} CACHE BOOL "Enable support for native file dialogs")
set(dtk_PYTHON OFF CACHE BOOL "Enable support for Python")
set(dtk_TESTS ON CACHE BOOL "Enable tests")
set(dtk_EXAMPLES ON CACHE BOOL "Enable examples")
if(APPLE)
    set(dtk_IGNORE_PREFIX_PATH_DEFAULT /opt/homebrew)
endif()
set(dtk_IGNORE_PREFIX_PATH ${dtk_IGNORE_PREFIX_PATH_DEFAULT} CACHE STRING "Ignore the given prefix path")
set(dtk_GCOV FALSE CACHE BOOL "Enable gcov code coverage")
set(dtk_GPROF FALSE CACHE BOOL "Enable gprof code profiling")

#-------------------------------------------------------------------------------
# Configuration

set(CMAKE_MODULE_PATH
    ${PROJECT_SOURCE_DIR}/cmake/Modules)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_FIND_FRAMEWORK LAST)

if(WIN32)
elseif(APPLE)
    set(CMAKE_SKIP_BUILD_RPATH FALSE)
    set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
    set(CMAKE_INSTALL_RPATH "@executable_path/../lib")
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
else()
    set(CMAKE_SKIP_BUILD_RPATH FALSE)
    set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
    set(CMAKE_INSTALL_RPATH "../lib")
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
endif()

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP")
endif()

if(dtk_UI_LIB)
    add_definitions(-DDTK_UI_LIB)
endif()

if(dtk_IGNORE_PREFIX_PATH)
    set(CMAKE_IGNORE_PREFIX_PATH ${dtk_IGNORE_PREFIX_PATH})
endif()

if(CMAKE_BUILD_TYPE MATCHES "^Debug$")
    add_definitions(-DDTK_ASSERT)
endif()

if(dtk_TESTS)
    set(CTEST_OUTPUT_ON_FAILURE ON)
    enable_testing()
endif()

if(dtk_GCOV)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")# -fkeep-inline-functions")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")# -fkeep-inline-functions")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()
if(dtk_GPROF)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pg")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include_directories(lib etc)
if(dtk_TESTS)
    include_directories(tests)
endif()

#-------------------------------------------------------------------------------
# Dependencies

find_package(Threads REQUIRED)
find_package(ZLIB REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(PNG REQUIRED)
find_package(Freetype REQUIRED)
find_package(lunasvg REQUIRED)

if(dtk_UI_LIB)
    if ("${dtk_API}" STREQUAL "GL_4_1")
        include_directories(${PROJECT_SOURCE_DIR}/deps/glad_GL_4_1/include)
    elseif ("${dtk_API}" STREQUAL "GL_4_1_Debug")
        include_directories(${PROJECT_SOURCE_DIR}/deps/glad_GL_4_1_Debug/include)
    elseif ("${dtk_API}" STREQUAL "GLES_2")
        include_directories(${PROJECT_SOURCE_DIR}/deps/glad_GLES_2/include)
    endif()
    if ("${dtk_API}" STREQUAL "GL_4_1" OR
        "${dtk_API}" STREQUAL "GL_4_1_Debug" OR
        "${dtk_API}" STREQUAL "GLES_2")
        find_package(OpenGL REQUIRED)
        find_package(glfw3 REQUIRED)
        add_subdirectory(deps/glad_${dtk_API})
    endif()
    add_definitions(-Ddtk_API_${dtk_API})
    if(${dtk_API} STREQUAL "GL_4_1_Debug")
        add_definitions(-Ddtk_API_GL_4_1)
    endif()

    if(dtk_NFD)
        find_package(NFD REQUIRED)
        if(NFD_FOUND)
            add_definitions(-Ddtk_NFD)
        endif()
    endif()

    if(dtk_PYTHON)
        include_directories(python/lib)
        if(dtk_TESTS)
            include_directories(python/tests)
        endif()
        add_definitions(-Ddtk_PYTHON)
        find_package(Python3 REQUIRED Interpreter Development)
        find_package(pybind11 REQUIRED)
    endif()
endif()

#-------------------------------------------------------------------------------
# Subdirectories

add_subdirectory(lib/dtk)
add_subdirectory(bin)
if(dtk_UI_LIB AND dtk_PYTHON)
    add_subdirectory(python)
endif()
if(dtk_TESTS)
    add_subdirectory(tests)
endif()
if(dtk_UI_LIB AND dtk_EXAMPLES)
    add_subdirectory(examples)
endif()

install(
    FILES cmake/Modules/FindZLIB.cmake
    DESTINATION lib/cmake/dtk)
install(
    FILES cmake/Modules/FindPNG.cmake
    DESTINATION lib/cmake/dtk)
if(dtk_UI_LIB)
    install(
        FILES cmake/Modules/FindNFD.cmake
        DESTINATION lib/cmake/dtk)
endif()
include(CMakePackageConfigHelpers)
set(INCLUDE_INSTALL_DIR include/dtk)
configure_package_config_file(
    dtkConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/dtkConfig.cmake
    INSTALL_DESTINATION lib/cmake/dtk
    PATH_VARS INCLUDE_INSTALL_DIR)
install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/dtkConfig.cmake
    DESTINATION lib/cmake/dtk)
