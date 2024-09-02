add_executable(dock dock.h dock.cpp)
target_link_libraries(dock dtkUI)
set_target_properties(dock PROPERTIES FOLDER examples)

add_test(NAME dock COMMAND dock -exit -log)
