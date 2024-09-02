add_executable(filebrowser filebrowser.cpp)
target_link_libraries(filebrowser dtkUI)
set_target_properties(filebrowser PROPERTIES FOLDER examples)

add_test(NAME filebrowser COMMAND filebrowser -exit -log)
