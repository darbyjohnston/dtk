set(HEADERS
    App.h)
set(PRIVATE_HEADERS)

set(SOURCE
    App.cpp
    main.cpp)

add_executable(dtkresource ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(dtkresource)
set_target_properties(dtkresource PROPERTIES FOLDER bin)

install(TARGETS dtkresource
    EXPORT dtkresourceTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)
install(
    EXPORT dtkresourceTargets
    FILE dtkresourceTargets.cmake
    DESTINATION "lib/cmake/dtk"
    NAMESPACE dtk::)
