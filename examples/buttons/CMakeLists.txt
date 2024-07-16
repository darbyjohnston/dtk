add_executable(buttons buttons.cpp)
target_link_libraries(buttons dtkUIApp)
set_target_properties(buttons PROPERTIES FOLDER examples)

install(TARGETS buttons
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

add_test(NAME buttons COMMAND buttons -exit -log)
