# Find the native file dialog extended library.
#
# This module defines the following variables:
#
# * nfd_INCLUDE_DIRS
# * nfd_LIBRARIES
#
# This module defines the following imported targets:
#
# * nfd::nfd
#
# This module defines the following interfaces:
#
# * nfd

if(WIN32)
elseif(APPLE)
else()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
endif()

find_path(nfd_INCLUDE_DIR NAMES nfd.h)
set(nfd_INCLUDE_DIRS
    ${nfd_INCLUDE_DIR}
    ${GTK3_INCLUDE_DIRS})

find_library(nfd_LIBRARY NAMES nfd)
set(nfd_LIBRARIES
    ${nfd_LIBRARY})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    nfd
    REQUIRED_VARS nfd_INCLUDE_DIR nfd_LIBRARY)
mark_as_advanced(nfd_INCLUDE_DIR nfd_LIBRARY)

set(nfd_COMPILE_DEFINITIONS nfd_FOUND)

set(nfd_LINK_LIBRARIES)
set(nfd_LINK_LIBRARIES)
if(WIN32)
    list(APPEND nfd_LINK_LIBRARIES ole32 uuid shell32)
elseif(APPLE)
    list(APPEND nfd_LINK_LIBRARIES "-framework AppKit")
else()
    list(APPEND nfd_LINK_LIBRARIES ${GTK3_LINK_LIBRARIES})
endif()

if(nfd_FOUND AND NOT TARGET nfd::nfd)
    add_library(nfd::nfd UNKNOWN IMPORTED)
    set_target_properties(nfd::nfd PROPERTIES
        IMPORTED_LOCATION "${nfd_LIBRARY}"
        INTERFACE_COMPILE_DEFINITIONS "${nfd_COMPILE_DEFINITIONS}"
        INTERFACE_INCLUDE_DIRECTORIES "${nfd_INCLUDE_DIRS}"
        INTERFACE_LINK_LIBRARIES "${nfd_LINK_LIBRARIES}")
endif()
if(nfd_FOUND AND NOT TARGET nfd)
    add_library(nfd INTERFACE)
    target_link_libraries(nfd INTERFACE nfd::nfd)
endif()
