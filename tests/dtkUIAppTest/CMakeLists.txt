set(HEADERS
    AppTest.h)
set(PRIVATE_HEADERS)

set(SOURCE
    AppTest.cpp)

add_library(dtkUIAppTest ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(dtkUIAppTest dtkUIApp dtkTestLib)
set_target_properties(dtkUIAppTest PROPERTIES FOLDER tests)
set_target_properties(dtkUIAppTest PROPERTIES PUBLIC_HEADER "${HEADERS}")

