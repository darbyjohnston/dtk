include(ExternalProject)

set(feather_tk_ARGS
    ${feather_tk_DEPS_ARGS}
    -Dfeather_tk_UI_LIB=${feather_tk_UI_LIB}
    -Dfeather_tk_API=${feather_tk_API}
    -Dfeather_tk_nfd=${feather_tk_nfd}
    -Dfeather_tk_PYTHON=${feather_tk_PYTHON}
    -Dfeather_tk_TOOLS_INSTALL=${feather_tk_TOOLS_INSTALL}
    -Dfeather_tk_TESTS=${feather_tk_TESTS}
    -Dfeather_tk_EXAMPLES=${feather_tk_EXAMPLES}
    -Dfeather_tk_GCOV=${feather_tk_GCOV}
    -Dfeather_tk_GPROF=${feather_tk_GPROF})

ExternalProject_Add(
    feather-tk
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/feather-tk
    DEPENDS ${feather_tk_DEPS}
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..
    LIST_SEPARATOR |
    CMAKE_ARGS ${feather_tk_ARGS})

