set(HEADERS ITest.h)
set(PRIVATE_HEADERS)

set(SOURCE ITest.cpp)

add_library(dtkTestLib ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(dtkTestLib dtkCore)
set_target_properties(dtkTestLib PROPERTIES FOLDER tests)
set_target_properties(dtkTestLib PROPERTIES PUBLIC_HEADER "${HEADERS}")

