
if(CMAKE_CROSSCOMPILING)
    include(Coverage)
endif(CMAKE_CROSSCOMPILING)

find_package(QtTestUtil)

if(${QT5})
    # Instruct CMake to run moc automatically when needed.
    set(CMAKE_AUTOMOC OFF)

    # cmake example from http://qt-project.org/doc/qt-5.0/qtdoc/cmake-manual.html
    find_package(Qt5Test)

else(${QT5})

    find_package(Qt4 4.8  REQUIRED QtTest)
    include(${QT_USE_FILE})

endif(${QT5})

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/testconfig.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/testconfig.h"
  )

include_directories(../src ${CMAKE_CURRENT_BINARY_DIR}/../src ${QT_TEST_UTIL_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

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
qt_test(pjerror pjerrortest.cpp)
qt_test(callInfo callinfotest.cpp)
qt_test(accountInfo accountinfotest.cpp)

# Maintest
if(${QT5})
    qt5_wrap_cpp(MOC_OUTPUT output.h)
else(${QT5})
    qt4_wrap_cpp(MOC_OUTPUT output.h)
endif(${QT5})
add_executable(qpjsuaTest maintest.cpp output.cpp ${MOC_OUTPUT})
target_link_libraries(qpjsuaTest qpjsua ${PJSIP_LIBRARIES} ${QT_LIBRARIES})

if(${QT5})
    qt5_use_modules(qpjsuaTest Core)
endif(${QT5})
