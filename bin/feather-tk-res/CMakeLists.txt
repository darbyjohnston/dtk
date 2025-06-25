set(HEADERS
    App.h)
set(PRIVATE_HEADERS)

set(SOURCE
    App.cpp
    main.cpp)

add_executable(feather-tk-res ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(feather-tk-res)
set_target_properties(feather-tk-res PROPERTIES FOLDER bin)

set(RUNTIME_DESTINATION "bin")
if(feather_tk_BUILD STREQUAL "vcpkg")
    set(RUNTIME_DESTINATION "tools/dtk")
endif()
install(TARGETS feather-tk-res
    EXPORT feather-tk-resTargets
    RUNTIME DESTINATION ${RUNTIME_DESTINATION})
install(
    EXPORT feather-tk-resTargets
    FILE feather-tk-resTargets.cmake
    DESTINATION "share/feather-tk"
    NAMESPACE feather-tk::)
