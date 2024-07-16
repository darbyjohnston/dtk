set(HEADERS
    App.h
    TextWidget.h
    Window.h)

set(SOURCE
    App.cpp
    TextWidget.cpp
    Window.cpp
    main.cpp)

add_executable(textedit ${HEADERS} ${SOURCE})
target_link_libraries(textedit dtkUIApp)
set_target_properties(textedit PROPERTIES FOLDER examples)

install(TARGETS textedit
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

add_test(NAME textedit COMMAND textedit -exit -log)