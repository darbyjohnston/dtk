add_executable(sliders sliders.cpp)
target_link_libraries(sliders dtkUIApp)
set_target_properties(sliders PROPERTIES FOLDER examples)

install(TARGETS sliders
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

add_test(NAME sliders COMMAND sliders -exit -log)