add_executable(filebrowser filebrowser.cpp)
target_link_libraries(filebrowser dtkUIApp)
set_target_properties(filebrowser PROPERTIES FOLDER examples)

install(TARGETS filebrowser
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

add_test(NAME filebrowser COMMAND filebrowser -exit -log)
