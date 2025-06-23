set(HEADERS
    App.h)
set(PRIVATE_HEADERS)

set(SOURCE
    App.cpp
    main.cpp)

add_executable(dtkres ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(dtkres)
set_target_properties(dtkres PROPERTIES FOLDER bin)

install(TARGETS dtkres
    EXPORT dtkresTargets
    RUNTIME DESTINATION ${dtk_TOOLS_INSTALL})
install(
    EXPORT dtkresTargets
    FILE dtkresTargets.cmake
    DESTINATION "share/dtk"
    NAMESPACE dtk::)
