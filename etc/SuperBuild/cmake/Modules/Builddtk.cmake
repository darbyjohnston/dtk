include(ExternalProject)

set(dtk_ARGS
    ${dtk_DEPS_ARGS}
    -Ddtk_UI_LIB=${dtk_UI_LIB}
    -Ddtk_API=${dtk_API}
    -Ddtk_nfd=${dtk_nfd}
    -Ddtk_PYTHON=${dtk_PYTHON}
    -Ddtk_TOOLS_INSTALL=${dtk_TOOLS_INSTALL}
    -Ddtk_TESTS=${dtk_TESTS}
    -Ddtk_EXAMPLES=${dtk_EXAMPLES}
    -Ddtk_GCOV=${dtk_GCOV}
    -Ddtk_GPROF=${dtk_GPROF})

ExternalProject_Add(
    dtk
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/dtk
    DEPENDS ${dtk_DEPS}
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..
    LIST_SEPARATOR |
    CMAKE_ARGS ${dtk_ARGS})

