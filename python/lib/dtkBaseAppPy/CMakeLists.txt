set(HEADERS
    Bindings.h
    CmdLine.h
    IApp.h)
set(HEADERS_PRIVATE)
set(SOURCE
    Bindings.cpp
    CmdLine.cpp
    IApp.cpp)

add_library(dtkBaseAppPy ${HEADERS} ${HEADERS_PRIVATE} ${SOURCE})
target_link_libraries(dtkBaseAppPy dtkBaseApp Python3::Python)
set_target_properties(dtkBaseAppPy PROPERTIES FOLDER python/lib)
set_target_properties(dtkBaseAppPy PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS dtkBaseAppPy
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/dtk/dtkBaseAppPy)
