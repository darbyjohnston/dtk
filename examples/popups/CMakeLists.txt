add_executable(popups popups.h popups.cpp)
target_link_libraries(popups dtkUI)
set_target_properties(popups PROPERTIES FOLDER examples)

add_test(NAME popups COMMAND popups -exit -log)