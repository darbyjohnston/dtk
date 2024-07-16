add_executable(popups popups.h popups.cpp)
target_link_libraries(popups dtkUIApp)
set_target_properties(popups PROPERTIES FOLDER examples)

install(TARGETS popups
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

add_test(NAME popups COMMAND popups -exit -log)