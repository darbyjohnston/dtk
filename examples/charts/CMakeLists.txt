add_executable(charts charts.cpp)
target_link_libraries(charts dtkUIApp)
set_target_properties(charts PROPERTIES FOLDER examples)

install(TARGETS charts
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

add_test(NAME charts COMMAND charts -exit -log)
