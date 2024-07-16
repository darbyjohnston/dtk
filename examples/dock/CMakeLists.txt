add_executable(dock dock.h dock.cpp)
target_link_libraries(dock dtkUIApp)
set_target_properties(dock PROPERTIES FOLDER examples)

install(TARGETS dock
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

add_test(NAME dock COMMAND dock -exit -log)
