set(HEADERS
    App.h)
set(PRIVATE_HEADERS)

set(SOURCE
    App.cpp)

add_library(dtkResourceApp ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(dtkResourceApp dtkBaseApp)
set_target_properties(dtkResourceApp PROPERTIES FOLDER lib)
set_target_properties(dtkResourceApp PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS dtkResourceApp
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/dtk/dtkResourceApp)

