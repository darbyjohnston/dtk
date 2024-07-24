set(HEADERS
    IApp.h
    CmdLineInline.h
    CmdLine.h)
set(PRIVATE_HEADERS)

set(SOURCE
    IApp.cpp
    CmdLine.cpp)

add_library(dtkBaseApp ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(dtkBaseApp dtkCore)
set_target_properties(dtkBaseApp PROPERTIES FOLDER lib)
set_target_properties(dtkBaseApp PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(
    TARGETS dtkBaseApp
    EXPORT dtkBaseAppTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/dtk/dtkBaseApp)
install(
    EXPORT dtkBaseAppTargets
    FILE dtkBaseAppTargets.cmake
    DESTINATION "lib/cmake/dtk"
    NAMESPACE dtk::)
