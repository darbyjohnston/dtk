set(HEADERS
    AppTest.h
    CmdLineTest.h)
set(PRIVATE_HEADERS)

set(SOURCE
    AppTest.cpp
    CmdLineTest.cpp)

add_library(dtkBaseAppTest ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(dtkBaseAppTest dtkBaseApp dtkTestLib)
set_target_properties(dtkBaseAppTest PROPERTIES FOLDER tests)
set_target_properties(dtkBaseAppTest PROPERTIES PUBLIC_HEADER "${HEADERS}")

