pybind11_add_module(feather_tk Bindings.cpp)
target_link_libraries(feather_tk PRIVATE feather-tk-uiPy feather-tk-corePy)
set_target_properties(feather_tk PROPERTIES FOLDER python/lib)
set_target_properties(feather_tk PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS feather_tk
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)
