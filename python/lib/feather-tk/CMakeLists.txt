pybind11_add_module(feather-tk Bindings.cpp)
target_link_libraries(feather-tk PRIVATE feather-tk-uiPy feather-tk-corePy)
set_target_properties(feather-tk PROPERTIES FOLDER python/lib)
set_target_properties(feather-tk PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS feather-tk
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)
