add_executable(charts charts.cpp)
target_link_libraries(charts dtkUI)
set_target_properties(charts PROPERTIES FOLDER examples)

add_test(NAME charts COMMAND charts -exit -log)
