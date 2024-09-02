pybind11_add_module(dtk Bindings.cpp)
target_link_libraries(dtk PRIVATE dtkUIPy dtkCorePy)
set_target_properties(dtk PROPERTIES FOLDER python/lib)
set_target_properties(dtk PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS dtk
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)
