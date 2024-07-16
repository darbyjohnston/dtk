add_test(
    NAME "Python buttons"
    COMMAND ${Python3_EXECUTABLE} buttons.py -exit -log
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(
    NAME "Python mdi"
    COMMAND ${Python3_EXECUTABLE} mdi.py -exit -log
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(
    NAME "Python simple"
    COMMAND ${Python3_EXECUTABLE} simple.py -exit -log
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(
    NAME "Python sliders"
    COMMAND ${Python3_EXECUTABLE} sliders.py -exit -log
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
