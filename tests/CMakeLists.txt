
if(CMAKE_CROSSCOMPILING)
    include(Coverage)
endif(CMAKE_CROSSCOMPILING)

find_package(QtTestUtil)

find_package(Qt4 4.8  REQUIRED QtTest)
include(${QT_USE_FILE})

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/testconfig.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/testconfig.h"
  )

include_directories(../src ${CMAKE_CURRENT_BINARY_DIR}/../src ${QT_TEST_UTIL_INCLUDE_DIR})

set(test_additional_lib
    qpjsua
    ${PJSIP_LIBRARIES}
    ${QT_TEST_UTIL_LIBRARIES}
)

#set(test_additional
#    foo.cpp
#)

qt_test(foo exampletest.cpp)
qt_test(accountConfiguration accountconfigurationtest.cpp)
qt_test(loggingConfiguration loggingconfigurationtest.cpp)
qt_test(mediaConfiguration mediaconfigurationtest.cpp)
qt_test(transportConfiguration transportconfigurationtest.cpp)

#qt4_wrap_cpp(MOC_OUTFILES output.h)
add_executable(qpjsuaTest maintest.cpp) # output.cpp ${MOC_OUTFILES})
target_link_libraries(qpjsuaTest qpjsua ${PJSIP_LIBRARIES} ${QT_LIBRARIES})
