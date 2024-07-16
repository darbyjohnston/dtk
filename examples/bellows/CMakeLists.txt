add_executable(bellows bellows.cpp)
target_link_libraries(bellows dtkUIApp)
set_target_properties(bellows PROPERTIES FOLDER examples)

install(TARGETS bellows
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

add_test(NAME bellows COMMAND bellows -exit -log)
