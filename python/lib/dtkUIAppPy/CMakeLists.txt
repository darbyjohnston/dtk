set(HEADERS
    App.h
    Bindings.h
    Window.h)
set(HEADERS_PRIVATE)
set(SOURCE
    App.cpp
    Bindings.cpp
    Window.cpp)

add_library(dtkUIAppPy ${HEADERS} ${HEADERS_PRIVATE} ${SOURCE})
target_link_libraries(dtkUIAppPy dtkUIApp Python3::Python)
set_target_properties(dtkUIAppPy PROPERTIES FOLDER python/lib)
set_target_properties(dtkUIAppPy PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS dtkUIAppPy
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/dtk/dtkUIAppPy)
