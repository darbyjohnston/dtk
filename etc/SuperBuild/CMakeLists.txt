cmake_minimum_required(VERSION 3.22)
cmake_policy(SET CMP0091 NEW)
cmake_policy(SET CMP0114 NEW)
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

project(dtk-SuperBuild)

#-------------------------------------------------------------------------------
# Options

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
set(dtk_GCOV FALSE CACHE BOOL "Enable gcov code coverage")
set(dtk_GPROF FALSE CACHE BOOL "Enable gprof code profiling")

#-------------------------------------------------------------------------------
# Configuration

list(APPEND CMAKE_MODULE_PATH
    ${PROJECT_SOURCE_DIR}/../../cmake/Modules
    ${PROJECT_SOURCE_DIR}/cmake/Modules)

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
endif()
if(NOT BUILD_SHARED_LIBS)
    set(BUILD_SHARED_LIBS OFF)
endif()
if(NOT CMAKE_POSITION_INDEPENDENT_CODE)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>DLL)
set(CMAKE_FIND_FRAMEWORK LAST)

# https://stackoverflow.com/questions/45414507/pass-a-list-of-prefix-paths-to-externalproject-add-in-cmake-args
string(REPLACE ";" "|" CMAKE_MODULE_PATH_TMP "${CMAKE_MODULE_PATH}")
string(REPLACE ";" "|" CMAKE_PREFIX_PATH_TMP "${CMAKE_PREFIX_PATH}")

set(dtk_DEPS_ARGS
    -DCMAKE_MODULE_PATH=${CMAKE_MODULE_PATH_TMP}
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
    -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH_TMP}
    -DCMAKE_POLICY_DEFAULT_CMP0091:STRING=NEW
    -DCMAKE_POLICY_DEFAULT_CMP0114:STRING=NEW
    -DCMAKE_FIND_FRAMEWORK=${CMAKE_FIND_FRAMEWORK}
    -DCMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD}
    -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
    -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
    -DCMAKE_MSVC_RUNTIME_LIBRARY=${CMAKE_MSVC_RUNTIME_LIBRARY}
    -DCMAKE_VERBOSE_MAKEFILE=${CMAKE_VERBOSE_MAKEFILE}
    -DCMAKE_OSX_DEPLOYMENT_TARGET=${CMAKE_OSX_DEPLOYMENT_TARGET}
    -DCMAKE_OSX_ARCHITECTURES=${CMAKE_OSX_ARCHITECTURES}
    -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}
    -DCMAKE_POSITION_INDEPENDENT_CODE=${CMAKE_POSITION_INDEPENDENT_CODE})
string(REPLACE ";" " " dtk_DEPS_ARGS_TMP "${dtk_DEPS_ARGS}")
message("dtk_DEPS_ARGS: " ${dtk_DEPS_ARGS_TMP})

#-------------------------------------------------------------------------------
# Build

list(APPEND dtk_DEPS ZLIB)
list(APPEND dtk_DEPS nlohmann_json)
list(APPEND dtk_DEPS PNG)
list(APPEND dtk_DEPS Freetype)
if ("${dtk_API}" STREQUAL "GL_4_1" OR
    "${dtk_API}" STREQUAL "GL_4_1_Debug" OR
    "${dtk_API}" STREQUAL "GLES_2")
    list(APPEND dtk_DEPS glfw3)
endif()
if(dtk_NFD)
    list(APPEND dtk_DEPS NFD)
endif()
if(dtk_PYTHON)
    list(APPEND dtk_DEPS pybind11)
endif()

foreach(DEP ${dtk_DEPS})
    include(Build${DEP})
endforeach()

include(Builddtk)
